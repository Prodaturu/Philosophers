/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 08:50:23 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/04 10:14:05 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	syntax_error(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (printf("Error: Invalid arg count\n"), 1);
	if (ft_atoi(av[1]) < 2)
		return (printf("Error: Invalid philosopher count\n"), 1);
	if (ft_atoi(av[2]) < 60)
		return (printf("Error: Invalid time to die\n"), 1);
	if (ft_atoi(av[3]) < 60)
		return (printf("Error: Invalid time to eat\n"), 1);
	if (ft_atoi(av[4]) < 60)
		return (printf("Error: Invalid time to sleep\n"), 1);
	if (ac == 6 && ft_atoi(av[5]) < 0)
		return (printf("Error: Invalid eat count\n"), 1);
	while ((*av[i]))
	{
		if ((*av[i] < '0' || *av[i] > '9') && *av[i] != '+')
			return (printf("Error: Invalid arg\n"), 1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (syntax_error(ac, av))
		return (1);
	return (0);
}
