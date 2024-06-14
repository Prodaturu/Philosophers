/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 23:09:10 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/07 21:02:33 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_shared	shared;
	t_mutex		mutexes;
	t_philo		*philos;

	if (syntax_error(ac, av))
		return (1);
	if (!init_shared_struct(ac, av, &shared))
		return (1);
	if (!init_mutex(&mutexes))
		return (1);
	if (init_philo(&philos, &shared, &mutexes))
		return (1);
	if (!start_threads(philos))
		return (printf(ERROR "start_threads failed\n"), 1);
	return (0);
}

	// if (!init_philo(&shared, &mutexes, &philos))
	// 	return (1);
	// if (!start_threads(&shared, &mutexes, philos))
	// 	return (1);