/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:27:47 by vmoroz            #+#    #+#             */
/*   Updated: 2024/11/03 14:39:48 by vmoroz           ###   ########.fr       */
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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
}
