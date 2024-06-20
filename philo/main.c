/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 23:09:10 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/20 08:04:38 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief main function
 * 
 * @param ac number of arguments
 * @param av arguments
 * @return int 0 if success, 1 if error
 * 
 * @details main function
 * 1. check syntax error
 * 2. initialize shared struct, which holds all the shared data b/w phils
 * 3. initialize mutexes
 * 4. initialize philos struct, which holds info specific to each philo
 * 5. start and join threads
 * 6. return 0 if success, 1 if error
 * 
 * @note As we are not allowed to use exit() , we use return 0 or 1 to
 * 		indicate success or failure at every step where we weould have
 * 		used exit(1) or exit(0)
 * 		Then we use those return values to dictate the return in main
 */

int	main(int ac, char **av)
{
	t_shared	shared;
	t_mutex		mutexes;
	t_philo		*philos;

	if (DEBUG_SWITCH)
		printf(OUTPUT "-----\t started philo program \t-----\n\n" RESET);
	if (syntax_error(ac, av))
		return (1);
	if (!init_shared_struct(ac, av, &shared))
		return (1);
	if (!init_mutex(&mutexes))
		return (1);
	if (init_philo(&philos, &shared, &mutexes))
		return (1);
	// start and join threads for each philosopher
	if (!start_threads(philos))
		return (printf(ERROR "start_threads failed\n" RESET), 1);
	if (DEBUG_SWITCH)
		printf(OUTPUT "\n-----\t Ended philo program \t-----\n\n");
	return (0);
}

/* Deatiled explanation of all functions in the file: */

/* --- Main function --- */

// The main function is the entry point of the program.
// It takes the number of arguments and the arguments themselves as parameters.
// It returns an integer value.
// As we are supposed to have a thread for each philosopher,
// we need to create a thread for each philosopher.
// If any of the functions return 1, it means there was an error
// and the main function returns 1.
// If all the functions return 0, it means the program ran successfully
// and the main function returns 0.
