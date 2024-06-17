/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:04:32 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/18 01:05:28 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*is_full(void *philos)
{
	t_philo	*philo;
	int		full;
	int		i;

	philo = philos;
	while (1)
	{
		i = -1;
		full = 0;
		while (++i < philo->shared->philo_count)
		{
			if (philo[i].is_done == 1)
				full++;
		}
		if (full == philo->shared->philo_count)
			return (philo->shared->is_full = 1, NULL);
		if (philo->shared->is_dead)
			return (NULL);
		usleep(10);
	}
	return (NULL);
}

void	*is_dead(void *philos)
{
	t_philo	*philo;
	size_t	time;
	int		i;

	philo = philos;
	i = -1;
	while (++i < philo->shared->philo_count)
	{
		pthread_mutex_lock(&philo[i].mutexes->lock_dead);
		time = get_curr_time();
		if (philo[i].death_time <= time - philo[i].last_meal_time)
		{
			pthread_mutex_lock(&philo[i].mutexes->lock_print);
			philo[i].shared->is_dead = 1;
			printf("%lu %d died\n", time - philo[i].shared->start_time, \
				philo[i].id);
			usleep(10);
			pthread_mutex_unlock(&philo[i].mutexes->lock_print);
			return (pthread_mutex_unlock(&philo[i].mutexes->lock_dead), NULL);
		}
		pthread_mutex_unlock(&philo[i].mutexes->lock_dead);
		if (i == philo->shared->philo_count - 1)
			i = -1;
	}
	return (NULL);
}
