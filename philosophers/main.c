/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:08:03 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/17 05:58:12 by sprodatu         ###   ########.fr       */
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
	t_philo		*philos;

	if (FASAK)
		printf(OUTPUT "-----\t started main fn\t-----\n" RESET);
	if (syntax_error(argc, argv))
		return (1);
	if (init_shared(&shared, argc, argv))
		return (1);
	if (init_philos(&shared, &philos))
		return (1);
	if (start_threads(&shared, philos))
		return (1);
	if (FASAK)
		printf(OUTPUT "-----\t finished main fn\t-----\n" RESET);
	return (0);
}
