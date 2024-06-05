/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:24:29 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/05 05:29:13 by sprodatu         ###   ########.fr       */
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
// # define FASAK 0

# define FASAK 1

typedef enum e_state {
	FORKING,
	EATING,
	SLEEPING,
	THINKING,
	DEAD_AF
}			t_state;

// Data common to all philosophers
typedef struct s_shared_data {
	int		philo_count;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	min_meals;
	size_t	start_time;
}				t_shared_data;

// Mutexes and synchronization data
typedef struct s_mutex_data {
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_done;
	pthread_mutex_t	lock_print;
}				t_mutex_data;

typedef struct s_philo_data {
	pthread_t		thread;
	int				id;
	int				death_time;
	int				meal_done_count;
	int				last_meal_time;
	bool			is_done;
	t_shared_data	*shared;
	t_mutex_data	*mutexes;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	lock_eating;
}	t_philo_data;

//: --------- syntax_check.c --------- ://
int					syntax_error(int ac, char **av);

//: --------- struct_init.c --------- ://
int					ft_atoi(const char *str);
int					init_shared_struct(int ac, char **av, t_shared_data *data);
int					init_mutex_data(t_mutex_data *data);*

#endif
