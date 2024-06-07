/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:50:08 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/07 20:53:07 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->shared->is_dead)
	{
		printf("Philosopher %d is thinking.\n", philo->id);
		pthread_mutex_lock(&philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		printf("Philosopher %d picked up forks.\n", philo->id);
		pthread_mutex_lock(&philo->lock_eating);
		philo->last_meal_time = get_curr_time();
		philo->meal_done_count++;
		printf("Philosopher %d is eating.\n", philo->id);
		pthread_mutex_unlock(&philo->lock_eating);
		usleep(philo->shared->time_to_eat * 1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		printf("Philosopher %d put down forks.\n", philo->id);
		printf("Philosopher %d is sleeping.\n", philo->id);
		usleep(philo->shared->time_to_sleep * 1000);
	}
	return (NULL);
}
