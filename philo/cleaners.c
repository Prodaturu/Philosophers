/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:43:30 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/07 19:14:13 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup_philo(t_philo **philos, int id)
{
	while (id > 0)
	{
		id--;
		pthread_mutex_destroy(&(*philos)[id].r_fork);
		pthread_mutex_destroy(&(*philos)[id].lock_eating);
	}
	free(*philos);
}
