/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:23:26 by vmoroz            #+#    #+#             */
/*   Updated: 2024/10/30 17:49:24 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	free(g->philo);
}

unsigned int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	new;

	i = 0;
	sign = 1;
	while (((str[i] == ' ' || (str[i] > 8 && str[i] < 14))) && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+' || str[i] < '0' || str[i] > '9')
		return (0);
	new = 0;
	while ((str[i] >= '0' && str[i] <= '9') || str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		new = (new * 10) + (str[i] - '0');
		i++;
	}
	return (sign * new);
}

int	main(int argc, char **argv)
{
	t_data	g;

	parser(&g, argc, argv);
	init(&g);
	while (check_if_dead(&g) == 0)
		keep_going_check(&g);
	thread_destroyer(&g);
	return (0);
}
