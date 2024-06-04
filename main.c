/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 08:50:23 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/05 00:13:24 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_shared_data	data;

	if (syntax_error(ac, av))
		return (1);
	if (!init_shared_struct(ac, av, &data))
		return (1);
	return (0);
}
