/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avg_it_student.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:23:54 by vmoroz            #+#    #+#             */
/*   Updated: 2024/10/28 18:29:21 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lock(t_data *g, int me, int beside)
{
	pthread_mutex_lock(&g->philo[beside].fork);
	check_if_dead(g);
	pthread_mutex_lock(&g->philo[me].fork);
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
	pthread_mutex_unlock(&g->philo[beside].fork);
	pthread_mutex_unlock(&g->philo[me].fork);
	if (!check_if_dead(g))
		printf("%lld Chel number %d is sleeping \n", time_ms(g), p->nb);
	else
		return ;
	usleep(g->t_sleep * 1000);
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
		check_if_dead(g);
		usleep(g->t_eat * 1000);
		check_if_dead(g);
	}
	sleeping(g, p);
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