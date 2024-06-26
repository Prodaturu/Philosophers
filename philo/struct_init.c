/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:43:23 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/20 15:12:31 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Init shared struct
 * @param ac
 * @param av
 * @param data
 * @return int
 * 
 * @details Init and fill struct with data from argv
 * Note: if min_meals not given it's -1
 * Note: start_time is set to current time
 * Note: DEBUG_SWITCH is used for debugging
*/

int	init_shared_struct(int ac, char **av, t_shared *data)
{
	if (DEBUG_SWITCH)
		printf(OUTPUT "----- \t started init_shared_struct \t-----\n");

	// assign given input values common to philos to shared struct
	data->philo_count = ft_atozu(av[1]);
	data->time_to_die = ft_atozu(av[2]);
	data->time_to_eat = ft_atozu(av[3]);
	data->time_to_sleep = ft_atozu(av[4]);
	data->min_meals = -1;

	// assign a variable to track if a philo is dead
	// as all philos die at the same time, we can use a single variable
	data->is_dead = 0;
	if (ac == 6)
		data->min_meals = ft_atozu(av[5]);
	data->start_time = get_curr_time();
	if (DEBUG_SWITCH)
		printf(OUTPUT "-----\t Ended init_shared_struct \t-----\n\n");
	return (1);
}

/**
 * @brief Init mutex data
 * @param data
 * @return int
 * 
 * @details Init mutexes for dead, done and print
 * Note: DEBUG_SWITCH is used for debugging
 * Note: if mutex init fails, destroy previous mutexes and return 0
 * 
*/

int	init_mutex(t_mutex *data)
{
	if (DEBUG_SWITCH)
		printf(OUTPUT "-----\t started init_mutex \t-----\n");
	if (pthread_mutex_init(&data->lock_dead, NULL) != 0)
		return (printf(ERROR "pthread_mutex_init for lock_dead failed.\n"), 0);
	if (pthread_mutex_init(&data->lock_done, NULL) != 0)
		return (pthread_mutex_destroy(&data->lock_dead),
			printf(ERROR "pthread_mutex_init for lock_done failed.\n"), 0);
	if (pthread_mutex_init(&data->lock_print, NULL) != 0)
		return (pthread_mutex_destroy(&data->lock_dead),
			pthread_mutex_destroy(&data->lock_done),
			printf(ERROR "pthread_mutex_init for lock_print failed.\n"), 0);
	if (DEBUG_SWITCH)
		printf(OUTPUT "-----\t Ended init_mutex \t-----\n\n");
	return (1);
}

/**
 * @brief Init philo data
 * @param shared
 * 
*/

void	init_single_philo(t_philo *philo, int id, t_shared *shared, \
	t_mutex *mutexes)
{
	philo->id = id + 1;
	philo->death_time = shared->time_to_die;
	philo->meal_count = 0;
	philo->last_meal_time = shared->start_time;
	philo->is_done = 0;
	philo->shared = shared;
	philo->mutexes = mutexes;
}

int	init_philo(t_philo **philos, t_shared *shared, t_mutex *mutexes)
{
	int		id;

	if (DEBUG_SWITCH)
		printf(OUTPUT "-----\t started init_philo \t-----\n");
	*philos = malloc(sizeof(t_philo) * shared->philo_count);
	if (!*philos)
		return (printf(ERROR "malloc fail for philos\n" RESET), 0);
	id = -1;
	while (++id < shared->philo_count)
	{
		init_single_philo(&(*philos)[id], id, shared, mutexes);
		if (pthread_mutex_init(&(*philos)[id].r_fork, NULL) != 0)
			return (cleanup_philo(philos, id),
				printf(ERROR "r_fork pthread_mutex_init fail\n"), 0);
		if (pthread_mutex_init(&(*philos)[id].lock_eating, NULL) != 0)
			return (pthread_mutex_destroy(&(*philos)[id].r_fork),
				cleanup_philo(philos, id),
				printf(ERROR "lock_eating pthread_mutex_init fail\n"), 0);
		if (id > 0)
			(*philos)[id].l_fork = &(*philos)[id - 1].r_fork;
	}
	
	if (shared->philo_count > 1)
		(*philos)[0].l_fork = &(*philos)[shared->philo_count - 1].r_fork;
	if (DEBUG_SWITCH)
		printf(OUTPUT "-----\t Ended init_philo \t-----\n\n");
	return (0);
}

int	start_threads(t_philo *philos)
{
	pthread_t		dead;
	pthread_t		full;
	int				id;

	id = 0;
	philos->shared->is_full = 0;
	philos->shared->is_dead = 0;
	philos->is_done = 0;
	pthread_create(&dead, NULL, is_dead, philos);
	pthread_create(&full, NULL, is_full, philos);
	while (id < philos[0].shared->philo_count)
	{
		if (pthread_create(&philos[id].thread, NULL, philo_routine, \
			&philos[id]) != 0)
			return (printf(ERROR "ERROR! pthread_create failed\n"), 0);
		id++;
	}
	if (DEBUG_SWITCH)
		printf(OUTPUT "-----\t Created all threads -----\n\n-----\t \
		Joining threads -----\n" RESET);
	id = -1;
	while (++id < philos[0].shared->philo_count)
		pthread_join(philos[id].thread, NULL);
	return (pthread_join(dead, NULL), pthread_join(full, NULL), (1));
}
