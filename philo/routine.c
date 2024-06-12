/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:50:08 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/07 21:40:33 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philo *philo, const char *action)
{
	size_t	timestamp;

	timestamp = get_curr_time() - philo->shared->start_time;
	printf("%zu %d %s\n", timestamp, philo->id, action);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->shared->is_dead)
	{
		print_action(philo, "is thinking");
		pthread_mutex_lock(&philo->r_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->lock_eating);
		philo->last_meal_time = get_curr_time();
		philo->meal_done_count++;
		print_action(philo, "is eating");
		pthread_mutex_unlock(&philo->lock_eating);
		usleep(philo->shared->time_to_eat * 1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		print_action(philo, "is sleeping");
		usleep(philo->shared->time_to_sleep * 1000);
	}
	return (NULL);
}
// Explanation
// Timestamp Calculation:

// The get_curr_time function returns the current time in milliseconds.
// The print_action function calculates the timestamp
// by subtracting philo->shared->start_time from the current time.
// Print Statements:

// The print_action function is used to print actions with the correct format.
// It prints the timestamp, philosopher ID, and action.
// Action Descriptions:

// Each action (thinking, taking a fork, eating, and sleeping)
// is logged using the print_action function,
// ensuring the output is consistent with the required format.
