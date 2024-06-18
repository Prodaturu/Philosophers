/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:50:08 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/18 03:27:57 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_initial_setup(t_philo *philo)
{
	if (philo->id % 2 == 0 || philo->id == philo->shared->philo_count)
	{
		print_action(philo, "is thinking");
		ft_usleep(philo->shared->time_to_eat);
	}
}

void	philo_eating_phase(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->lock_eating);
	print_action(philo, "is eating");
	philo->last_meal_time = get_curr_time();
	philo->meal_count++;
	if (philo->meal_count == (int)philo->shared->min_meals)
		philo->is_done = 1;
	ft_usleep(philo->shared->time_to_eat);
	pthread_mutex_unlock(&philo->lock_eating);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void	philo_sleeping_thinking_phase(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->shared->time_to_sleep);
	if (philo->shared->is_dead || philo->shared->is_full)
		return ;
	print_action(philo, "is thinking");
}

void	*philo_main_routine(t_philo *philo)
{
	while (!philo->shared->is_dead)
	{
		if (philo->shared->is_dead || philo->shared->is_full)
			return (NULL);
		philo_eating_phase(philo);
		if (philo->shared->is_dead || philo->shared->is_full)
			return (NULL);
		philo_sleeping_thinking_phase(philo);
		if (philo->shared->is_dead || philo->shared->is_full)
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_initial_setup(philo);
	return (philo_main_routine(philo));
}

// // void	*philo_main_routine(t_philo *philo)
// // {
// // 	while (!philo->shared->is_dead)
// // 	{
// // 		if (philo->shared->is_dead || philo->shared->is_full)
// // 			return NULL;

// // 		pthread_mutex_lock(&philo->r_fork);
// // 		print_action(philo, "has taken a fork");
// // 		pthread_mutex_lock(philo->l_fork);
// // 		print_action(philo, "has taken a fork");
// // 		pthread_mutex_lock(&philo->lock_eating);
// // 		print_action(philo, "is eating");

// // 		philo->last_meal_time = get_curr_time();
// // 		philo->meal_count++;
// // 		if (philo->meal_count == (int)philo->shared->min_meals)
// // 			philo->is_done = 1;

// // 		ft_usleep(philo->shared->time_to_eat);
// // 		pthread_mutex_unlock(&philo->lock_eating);
// // 		pthread_mutex_unlock(philo->l_fork);
// // 		pthread_mutex_unlock(&philo->r_fork);

// // 		if (philo->shared->is_dead || philo->shared->is_full)
// // 			return NULL;

// // 		print_action(philo, "is sleeping");
// // 		ft_usleep(philo->shared->time_to_sleep);

// // 		if (philo->shared->is_dead || philo->shared->is_full)
// // 			return NULL;

// // 		print_action(philo, "is thinking");
// // 	}
// // 	return NULL;
// // }

// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 0 || philo->id == philo->shared->philo_count)
// 	{
// 		print_action(philo, "is thinking");
// 		ft_usleep(philo->shared->time_to_eat);
// 	}
// 	while (!philo->shared->is_dead)
// 	{
// 		if (philo->shared->is_dead || philo->shared->is_full)
// 			return (NULL);
// 		pthread_mutex_lock(&philo->r_fork);
// 		print_action(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->l_fork);
// 		print_action(philo, "has taken a fork");
// 		pthread_mutex_lock(&philo->lock_eating);
// 		print_action(philo, "is eating");
// 		philo->last_meal_time = get_curr_time();
// 		philo->meal_count++;
// 		if (philo->meal_count == (int)philo->shared->min_meals)
// 			philo->is_done = 1;
// 		ft_usleep(philo->shared->time_to_eat);
// 		pthread_mutex_unlock(&philo->lock_eating);
// 		pthread_mutex_unlock(philo->l_fork);
// 		pthread_mutex_unlock(&philo->r_fork);
// 		if (philo->shared->is_dead || philo->shared->is_full)
// 			return (NULL);
// 		print_action(philo, "is sleeping");
// 		ft_usleep(philo->shared->time_to_sleep);
// 		if (philo->shared->is_dead || philo->shared->is_full)
// 			return (NULL);
// 		print_action(philo, "is thinking");
// 		if (philo->shared->is_dead)
// 			return (NULL);
// 	}
// 	return (NULL);
// }

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
