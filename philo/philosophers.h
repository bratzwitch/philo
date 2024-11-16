/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:38:54 by vmoroz            #+#    #+#             */
/*   Updated: 2024/11/16 12:01:37 by vmoroz           ###   ########.fr       */
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
	int					fork_flag;
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

int						parser(t_data *d, int argc, char **argv);
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
size_t					get_current_time(void);
void					ft_usleep(size_t milliseconds);

#endif