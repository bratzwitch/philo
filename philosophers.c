/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:38:45 by vmoroz            #+#    #+#             */
/*   Updated: 2024/10/26 16:05:22 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*If someone dies, it will return 1*/
/*and stop the program right away*/
int	check_if_dead(t_data *g)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&g->dying);
	if (g->dead)
		flag += 1;
	pthread_mutex_unlock(&g->dying);
	if (flag != 0)
		return (1);
	return (0);
}

/*If anyone dies, the program will be ended,*/
	/*and prints that the philo have died*/
int	dead_checker(t_data *g)
{
	int	i;

	i = -1;
	while (++i < g->nb_philo)
	{
		pthread_mutex_lock(&g->eating);
		if (time_2_eat(&g->philo[i]) >= g->t_die)
		{
			printf("%lld %d died\n", time_ms(g), g->philo[i].nb);
			pthread_mutex_unlock(&g->eating);
			return (1);
		}
		pthread_mutex_unlock(&g->eating);
	}
	return (0);
}

/*Here it will see how many times each philo eat,*/
/*if it reaches the number passed in the argv[argc5]*/
/*then it will stop the program*/
int	eat_checker(t_data *g)
{
	int	i;

	if (g->t_x_eat == 0)
		return (0);
	i = -1;
	while (++i < g->nb_philo)
	{
		pthread_mutex_lock(&g->eating);
		if (g->philo[i].p_eat < g->t_x_eat)
		{
			pthread_mutex_unlock(&g->eating);
			return (0);
		}
		pthread_mutex_unlock(&g->eating);
	}
	return (1);
}

/*Checks if are any dead philo with the functions above*/
int	keep_going(t_data *g)
{
	if (dead_checker(g) || eat_checker(g))
	{
		pthread_mutex_lock(&g->dying);
		g->dead = 1;
		pthread_mutex_unlock(&g->dying);
		return (1);
	}
	return (0);
}

/*Again always checking if someone died, after*/
/*unlocks the forks it used to eat, and will start*/
/*"sleeping" with the usleep function and then */
/*print that exact same action*/
void	sleeping(t_data *g, t_philo *p)
{
	short	me;
	short	beside;

	me = p->nb;
	beside = p->nb - 1;
	if (p->nb == p->global->nb_philo)
	{
		me = beside;
		beside = 0;
	}
	pthread_mutex_unlock(&g->philo[beside].fork);
	pthread_mutex_unlock(&g->philo[me].fork);
	if (!check_if_dead(g))
		printf("%lld %d is sleeping \n", time_ms(g), p->nb);
	else
		return ;
	usleep(g->t_sleep * 1000);
	if (!check_if_dead(g))
		printf("%lld %d is thinking \n", time_ms(g), p->nb);
	else
		return ;
}

/*Here will check if one philo is dead, because */
/*they can die while wating as well, then prints */
/*the time, the id of the philo and that is eating*/
/*after eating checks if it died while eating and*/
/*if not, it calls the function sleeping above*/
void	print_eat(t_data *g, t_philo *p)
{
	if (!check_if_dead(g))
	{
		printf("%lld %d has taken a fork\n", time_ms(g), p->nb);
		printf("%lld %d has taken a fork\n", time_ms(g), p->nb);
		printf("%lld %d is eating\n", time_ms(g), p->nb);
		check_if_dead(g);
		usleep(g->t_eat * 1000);
		check_if_dead(g);
	}
	sleeping(g, p);
}

/*Here, the philo will check if the forks are */
/*unlocked or not, if they are, they will lock*/
/*them and start to eat, the prints come in the*/
/*print_eat function above*/
void	eat(t_data *g, t_philo *p)
{
	short	me;
	short	beside;

	me = p->nb;
	beside = p->nb - 1;
	if (p->nb == p->global->nb_philo)
	{
		me = beside;
		beside = 0;
	}
	if (check_if_dead(g))
		return ;
	ft_lock(g, me, beside);
	pthread_mutex_lock(&g->eating);
	gettimeofday(&p->time, NULL);
	p->p_eat++;
	if (check_if_dead(g))
	{
		pthread_mutex_unlock(&g->philo[me].fork);
		pthread_mutex_unlock(&g->philo[beside].fork);
		pthread_mutex_unlock(&g->eating);
		return ;
	}
	pthread_mutex_unlock(&g->eating);
	print_eat(g, p);
}

/*Checks if someone is dead again because*/
/*functions spend miliseconds as well*/
void	exec_philo(t_data *g, t_philo *p)
{
	if (check_if_dead(g))
		return ;
	eat(g, p);
	if (check_if_dead(g))
		return ;
}

/*This function is called in every philo thread*/
/*always checking if someone die and only then */
/*executes the routine and keeps looking for dead */
void	*exec(void *arg)
{
	t_philo	*p;
	t_data	*g;

	p = arg;
	g = p->global;
	while (1)
	{
		if (check_if_dead(g))
			return (arg);
		exec_philo(g, p);
		if (check_if_dead(g))
			return (arg);
	}
	return (arg);
}
void	init(t_data *g)
{
	int				i;

	i = -1;
	g->philo = malloc(sizeof(t_philo) * g->nb_philo);
	g->start_time = 0;
	while (++i < g->nb_philo)
		pthread_mutex_init(&g->philo[i].fork, NULL);
	pthread_mutex_init(&g->dying, NULL);
	pthread_mutex_init(&g->eating, NULL);
	i = -1;
	while (++i < g->nb_philo)
	{
		g->philo[i].nb = i + 1;
		g->philo[i].p_eat = 0;
		g->philo[i].global = g;
		if (i == 0)
			gettimeofday(&g->s_time, NULL);
		g->philo[i].time = g->s_time;
		pthread_create(&g->philo[i].philo, NULL, &exec, &g->philo[i]);
		usleep(1000);
	}
}
static void	checker(t_data *g, int argc, int i)
{
	if (g->nb_philo >= 1)
		i = 1;
	else
	{
		printf("Please set \e[1;36mat least 1 philosopher\e[0m\n");
		exit(EXIT_FAILURE);
	}
	if (g->t_die >= 0)
		i++;
	if (g->t_eat >= 0)
		i++;
	if (g->t_sleep >= 0)
		i++;
	if (argc == 6)
		if (g->t_x_eat >= 0)
			i++;
	if (argc == 5 && i == 4)
		return ;
	if (argc == 6 && i == 5)
		return ;
	printf(RED"🚨  ! Wrong arguments !  🚨\n"RES);
	printf("Please use only \e[1;36mvalid unsigned int \e[0mas arguments\n");
	printf(ORANGE1"No signs, no letters, no special chars\n"RES);
	free (g);
	exit (EXIT_FAILURE);
}

/*Init the global args passed by the user to a struct*/
static void	init_variables(t_data *g, int argc, char **argv)
{
	g->nb_philo = ft_atoi(argv[1]);
	g->t_die = ft_atoi(argv[2]);
	g->t_eat = ft_atoi(argv[3]);
	g->t_sleep = ft_atoi(argv[4]);
	g->dead = 0;
	if (argc == 6)
		g->t_x_eat = ft_atoi(argv[5]);
	else
		g->t_x_eat = 0;
}

/*Checks the number of argvs, and calls the functions*/
/*above to help it*/
void	parser(t_data *g, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf(RED"    🚨 !! Wrong number of arguments !! 🚨\n"RES);
		printf("Set \e[1;33m4 arguments\e[0m, number of philosophers");
		printf(", time to die, time to eat, time to sleep!\n");
		printf("You can set a \e[1;33m5th opcional argument \e[0mfor");
		printf(" number of times to eat\n");
		exit (EXIT_FAILURE);
	}
	init_variables(g, argc, argv);
	checker(g, argc, 0);
	if (g->nb_philo == 1)
	{
		usleep(g->t_die * 1000);
		printf("%lld %d died\n", g->t_die, 1);
		exit(EXIT_FAILURE);
	}
}
long long	time_2_eat(t_philo *p)
{
	struct timeval	tv;
	long long		sec;
	long long		usec;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec - p->time.tv_sec;
	usec = tv.tv_usec - p->time.tv_usec;
	return ((usec / 1000) + (sec * 1000));
}

/*Returns the current time in miliseconds*/
long long	time_ms(t_data *g)
{
	struct timeval	tv;
	long long		sec;
	long long		usec;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec - g->s_time.tv_sec;
	usec = tv.tv_usec - g->s_time.tv_usec;
	return ((usec / 1000) + (sec * 1000));
}

/*Join the threads so it doesn't leak and*/
/*also destoryes the mutexes*/
void	thread_destroyer(t_data *g)
{
	int	i;

	i = -1;
	while (++i < g->nb_philo)
		pthread_join(g->philo[i].philo, NULL);
	pthread_mutex_destroy(&g->dying);
	pthread_mutex_destroy(&g->eating);
	i = -1;
	while (++i < g->nb_philo)
		pthread_mutex_destroy(&g->philo[i].fork);
	free (g->philo);
}

/*Replica of atoi from stdlib*/
unsigned int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	new;

	i = 0;
	sign = 1;
	while (((str[i] == ' ' || (str[i] > 8 && str[i] < 14))) && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+'
		|| str[i] < '0' || str[i] > '9')
		return (-10);
	new = 0;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		new = (new * 10) + (str[i] - '0');
		i++;
	}
	return (sign * new);
}

void	ft_lock(t_data *g, int me, int beside)
{
	pthread_mutex_lock(&g->philo[beside].fork);
	check_if_dead(g);
	pthread_mutex_lock(&g->philo[me].fork);
}
int	main(int argc, char **argv)
{
	t_data	g;

	parser(&g, argc, argv);
	init(&g);
	while (check_if_dead(&g) == 0)
		keep_going(&g);
	thread_destroyer(&g);
	return (0);
}
