/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:43:23 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/05 00:12:18 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_shared_struct(int ac, char **av, t_shared_data *data)
{
	if (FASAK)
		printf("\033[0;32m-----\t started init_shared_struct -----\n\033[0m");
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->min_meals = ft_atoi(av[5]);
	else
		data->min_meals = -1;
	if (FASAK)
		printf("\033[0;32m-----\t Ended init_shared_struct -----\n\033[0m");
	return (1);
}
