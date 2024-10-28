/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:38:54 by vmoroz            #+#    #+#             */
/*   Updated: 2024/10/28 18:42:56 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define BLACK "\e[1;30m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define PURPLE "\e[1;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[1;37m"
# define RES "\e[0m"
# define ORANGE1 "\033[38;5;214m"
# define ORANGE2 "\033[38;5;202m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	short				nb;
	short				p_eat;
	struct timeval		time;
	pthread_mutex_t		fork;
	pthread_t			philo;
	t_data				*global;
}						t_philo;

typedef struct s_data
{
	short				nb_philo;
	short				*fork;
	struct timeval		s_time;
	pthread_mutex_t		dying;
	pthread_mutex_t		eating;
	long long			t_die;
	long long			t_eat;
	long long			t_sleep;
	long long			dead;
	long long			start_time;
	short				t_x_eat;
	t_philo				*philo;
}						t_data;

void					parser(t_data *d, int argc, char **argv);
void					*exec(void *arg);
void					print_eat(t_data *g, t_philo *p);
void					sleeping(t_data *g, t_philo *p);
void					init(t_data *g);
unsigned int			ft_atoi(const char *str);
long long				time_ms(t_data *g);
void					ft_lock(t_data *g, int me, int beside);
long long				time_2_eat(t_philo *p);
void					thread_destroyer(t_data *g);
int						keep_going_check(t_data *g);
int						check_if_dead(t_data *g);
void					ft_free(void **ptr);
void					eat(t_data *g, t_philo *p);

#endif