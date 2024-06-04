/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:24:29 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/05 00:14:45 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

// FASAK is used to test the code,
// FASAK -> 1 => test mode
// FASAK -> 0 => normal mode
// # define FASAK 1

# define FASAK 0

typedef enum e_state
{
	forking,
	eating,
	sleeping,
	thinking,
	dead_af
}	t_state;

typedef struct s_shared_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_meals;
}	t_shared_data;

//: --------- syntax_check.c --------- ://
int					syntax_error(int ac, char **av);

//: --------- struct_init.c --------- ://
int					ft_atoi(const char *str);
int					init_shared_struct(int ac, char **av, t_shared_data *data);
#endif
