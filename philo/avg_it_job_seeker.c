/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avg_it_job_seeker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:58:13 by vmoroz            #+#    #+#             */
/*   Updated: 2024/11/16 12:02:27 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lock(t_data *g, int me, int beside)
{
	int	first_fork;
	int	second_fork;

	first_fork = beside;
	second_fork = me;
	if (me < beside)
	{
		first_fork = me;
		second_fork = beside;
	}
	pthread_mutex_lock(&g->philo[first_fork].fork);
	if (check_if_dead(g))
	{
		pthread_mutex_unlock(&g->philo[first_fork].fork);
		return ;
	}
	pthread_mutex_lock(&g->philo[second_fork].fork);
	if (check_if_dead(g))
	{
		pthread_mutex_unlock(&g->philo[first_fork].fork);
		pthread_mutex_unlock(&g->philo[second_fork].fork);
		return ;
	}
}

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
	if (!check_if_dead(g))
		printf("%lld Chel number %d is sleeping \n", time_ms(g), p->nb);
	else
		return ;
	ft_usleep(g->t_sleep);
	if (!check_if_dead(g))
		printf("%lld Chel number %d is thinking \n", time_ms(g), p->nb);
	else
		return ;
}

void	print_eat(t_data *g, t_philo *p)
{
	if (!check_if_dead(g))
	{
		printf("%lld Chel number %d has taken a fork\n", time_ms(g), p->nb);
		printf("%lld Chel number %d has taken a fork\n", time_ms(g), p->nb);
		printf("%lld Chel number %d is eating\n", time_ms(g), p->nb);
	}
	check_if_dead(g);
	ft_usleep(g->t_eat);
	check_if_dead(g);
}

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
	pthread_mutex_unlock(&g->eating);
	if (check_if_dead(g))
		return ;
	print_eat(g, p);
	pthread_mutex_unlock(&g->philo[beside].fork);
	pthread_mutex_unlock(&g->philo[me].fork);
	sleeping(g, p);
}
