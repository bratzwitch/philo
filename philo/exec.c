/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:26:32 by vmoroz            #+#    #+#             */
/*   Updated: 2024/10/28 18:27:03 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exec_philo(t_data *g, t_philo *p)
{
	if (check_if_dead(g))
		return ;
	eat(g, p);
	if (check_if_dead(g))
		return ;
}

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
