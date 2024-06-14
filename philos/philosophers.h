/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:07:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/14 08:44:46 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// The <pthread.h> header file is used to create threads.

# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

// FASAK is used to test / debug code,
// FASAK -> 1 => test mode
// FASAK -> 0 => normal mode
// # define FASAK 1

# define FASAK 0

# define ERROR "\033[0;31m"		// Red
# define DEBUG "\033[0;34m"		// Blue
# define OUTPUT "\033[0;32m"	// Green
# define RESET "\033[0m"		// Reset color

// Data common to all philosophers

typedef struct s_shared
{
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				death;
	size_t			start_time;
	size_t			min_meals;
	int				done_count;
	pthread_mutex_t	lock_done;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_dead;
}					t_shared;

// Data specific to each philosopher

typedef struct s_philo
{
	pthread_t		thread;
	int				p_id;
	size_t			time_of_death;
	int				meal_count;
	int				is_done;
	t_shared		*shared;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	lock_eating;
}					t_philo;

//: ---------	syntax_check.c	--------- ://
size_t				ft_atozu(const char *str);
int					syntax_error(int ac, char **av);

//: ---------	struct_init.c	--------- ://
int					init_shared(t_shared *shared, int argc, char **argv);
int					init_philos(t_shared *shared, t_philo **philos);

#endif
