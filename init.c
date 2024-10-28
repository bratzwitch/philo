/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:25:47 by vmoroz            #+#    #+#             */
/*   Updated: 2024/10/28 18:44:28 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(t_data *g)
{
	int	i;

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
	printf(RED "🚨  ! Wrong arguments !  🚨\n" RES);
	printf("Please use only \e[1;36mvalid unsigned int \e[0mas arguments\n");
	printf(ORANGE1 "No signs, no letters, no special chars\n" RES);
	free(g);
	exit(EXIT_FAILURE);
}

void	parser(t_data *g, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Invalid num of args bro\n");
		printf("You need num_of_cheliks die_time eat_time sleep_time\n");
		printf("You can add 5th arg which will be how much they need to eat\n");
		exit(EXIT_FAILURE);
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
