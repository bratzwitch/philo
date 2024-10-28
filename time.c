/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:27:47 by vmoroz            #+#    #+#             */
/*   Updated: 2024/10/28 18:28:08 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
