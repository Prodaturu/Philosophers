/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:01:49 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/14 08:44:29 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_exit(t_shared *data, int num, int join, t_philo *philos)
{
	int		i;
	int		ret;

	i = -1;
	ret = 1;
	if (join == 1)
	{
		while (++i < num)
			if (philos[i].thread)
				if (pthread_join(philos[i].thread, NULL) != 0)
					ret = 0;
	}
	pthread_mutex_destroy(&data->lock_dead);
	pthread_mutex_destroy(&data->lock_done);
	pthread_mutex_destroy(&data->lock_print);
	while (philos != NULL && num--)
	{
		pthread_mutex_destroy(&philos[num].r_fork);
		pthread_mutex_destroy(&philos[num].lock_eating);
	}
	free(philos);
	return (ret);
}

int	init_philo_mutexes(t_philo *philo, t_shared *shared, int id)
{
	if (pthread_mutex_init(&philo->r_fork, NULL) != 0)
	{
		printf(ERROR "mutex_init for philo failed\n");
		return (ft_exit(shared, --id, 0, philo), 0);
	}
	if (pthread_mutex_init(&philo->lock_eating, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->r_fork);
		printf(ERROR "mutex_init failed\n");
		return (ft_exit(shared, --id, 0, philo), 0);
	}
	return (1);
}

int	init_philos(t_shared *shared, t_philo **philos)
{
	int	id;

	if (FASAK)
		printf(OUTPUT "-----\t started init_philo \t-----\n");
	id = 0;
	*philos = malloc(sizeof(t_philo) * (shared->philo_count));
	if (*philos == NULL)
		return (printf(ERROR "malloc fail\n"), ft_exit(shared, 0, 0, NULL), 0);
	while (++id <= shared->philo_count)
	{
		(*philos)[id - 1].p_id = id;
		(*philos)[id - 1].thread = 0;
		(*philos)[id - 1].meal_count = 0;
		(*philos)[id - 1].is_done = 0;
		(*philos)[id - 1].time_of_death = current_mtime() + shared->time_to_die;
		(*philos)[id - 1].shared = shared;
		if (!init_philo_mutexes(&(*philos)[id - 1], shared, id))
			return (0);
		if (id > 1)
			(*philos)[id - 1].l_fork = &(*philos)[id - 2].r_fork;
	}
	(*philos)[0].l_fork = &(*philos)[shared->philo_count - 1].r_fork;
	if (FASAK)
		printf(OUTPUT "-----\t finished init_philo \t-----\n" RESET);
	return (1);
}

/**
 * @brief Initialize mutexes
 * init mutex to lock done, print and dead
 * @param shared Shared data struct
 * @return int 1 if successful, 0 otherwise
*/

int	init_mutexes_shared(t_shared *shared)
{
	if (FASAK)
		printf(OUTPUT "-----\t started init_mutexes \t-----\n" RESET);
	if (pthread_mutex_init(&shared->lock_done, NULL) != 0)
	{
		printf(ERROR "Error: lock_done initialization failed.\n" RESET);
		return (0);
	}
	if (pthread_mutex_init(&shared->lock_print, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->lock_done);
		printf(ERROR "Error: lock_print initialization failed.\n" RESET);
		return (0);
	}
	if (pthread_mutex_init(&shared->lock_dead, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->lock_done);
		pthread_mutex_destroy(&shared->lock_print);
		printf(ERROR "Error: lock_dead initialization failed.\n" RESET);
		return (0);
	}
	if (FASAK)
		printf(OUTPUT "-----\t finished init_mutexes \t-----\n" RESET);
	return (1);
}

/**
 * Initializes shared data struct with provided command line arguments.
 *
 * @param argc num of command line arguments.
 * @param argv "Array of strings" containing arguments.
 * @param data Pointer to shared info struct.
 * @return true if the initialization is successful, false otherwise.
 */

int	init_shared(t_shared *shared, int argc, char **argv)
{
	if (FASAK)
		printf(OUTPUT "-----\t started init_shared \t-----\n");
	shared->philo_count = ft_atozu(argv[1]);
	shared->time_to_die = ft_atozu(argv[2]);
	shared->time_to_eat = ft_atozu(argv[3]);
	shared->time_to_sleep = ft_atozu(argv[4]);
	shared->death = 0;
	shared->done_count = 0;
	shared->start_time = get_curr_time();
	shared->min_meals = -1;
	if (argc == 6)
		shared->min_meals = ft_atozu(argv[5]);
	if (!init_mutexes_shared(shared))
		return (0);
	if (FASAK)
		printf(OUTPUT "-----\t finished init_shared \t-----\n" RESET);
	return (1);
}
