/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 08:50:23 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/05 20:38:33 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_shared_data	shared;
	t_mutex_data	mutexes;
	t_philo_data	*philos;

	if (syntax_error(ac, av))
		return (1);
	if (!init_shared_struct(ac, av, &shared))
		return (1);
	if (!init_mutex_data(&shared))
		return (1);
	return (0);
}

	// if (!init_philo_data(&shared, &mutexes, &philos))
	// 	return (1);
	// if (!start_threads(&shared, &mutexes, philos))
	// 	return (1);