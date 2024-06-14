/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:08:03 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/14 08:15:03 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief The main function of the program.
 * Check syntax, init shared and philo specific struct,
 * start the threads and run the process
 * clean and return
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return The exit status of the program.
 */

int	main(int argc, char **argv)
{
	t_shared	shared;

	if (syntax_error(argc, argv))
		return (1);
	if (init_shared(&shared, argc, argv))
		return (1);
	if (init_philos())
		return (1);
	if (start_threads(&shared))
		return (1);
	cleanup(&shared);
	return (0);
}
