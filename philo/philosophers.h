/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:24:29 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/20 17:31:22 by sprodatu         ###   ########.fr       */
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

// DEBUG_SWITCH is used to test / debug code,
// DEBUG_SWITCH -> 1 => test mode
// DEBUG_SWITCH -> 0 => normal mode
// # define DEBUG_SWITCH 1

# define DEBUG_SWITCH 0
# define DEBUG_ALL_SWITCH 0

# define ERROR "\033[0;31m"		// Red
# define DEBUG "\033[0;34m"		// Blue
# define OUTPUT "\033[0;32m"	// Green

# define FORK "\033[38;2;52;152;219m"    // #3498DB
# define EAT "\033[0;32m"
# define SLEEP "\033[38;2;189;195;199m"// #BDC3C7
# define THINK "\033[38;2;241;196;15m" // #F1C40F
# define RESET "\033[0m"		// Reset color

typedef enum e_state
{
	FORKING,
	EATING,
	SLEEPING,
	THINKING,
	DEAD_AF
}			t_state;

// Data common to all philosophers

typedef struct s_shared_data
{
	int				is_dead;
	int				is_full;
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			min_meals;
	size_t			start_time;
}				t_shared;

// Mutexes and synchronization data
typedef struct s_mutex_data {
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_done;
	pthread_mutex_t	lock_print;
}				t_mutex;

// Data specific to each philosopher

typedef struct s_philo_data
{
	pthread_t		thread;
	int				id;
	size_t			death_time;
	size_t			last_meal_time;
	int				meal_count;
	int				is_done;
	t_shared		*shared;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	lock_eating;
	t_mutex			*mutexes;
}	t_philo;

//: ---------	syntax_check.c	--------- ://
size_t				ft_atozu(const char *str);
int					error_in_arg(int ac, char **av);
int					syntax_error(int ac, char **av);

//: ---------	struct_init.c	--------- ://
int					init_shared_struct(int ac, char **av, t_shared *data);
int					init_mutex(t_mutex *data);
int					init_philo(t_philo **philos, t_shared *shared, \
t_mutex *mutexes);
int					start_threads(t_philo *philos);

//: ---------	time_vals.c	--------- ://
size_t				get_curr_time(void);

//: ---------	cleaners.c	--------- ://
void				cleanup_philo(t_philo **philos, int id);
int					ft_strcmp(const char *s1, const char *s2);


//: ---------	routine.c	--------- ://
void				*philo_routine(void *arg);

//: ---------	is_checks.c	--------- ://
void				*is_dead(void *philos);
void				*is_full(void *philos);
void				ft_usleep(int time);
void				print_action(t_philo *philo, const char *action);
#endif
