/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:41:25 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/05 17:13:50 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atozu(const char *str)
{
	size_t	res;
	int		i;

	res = 0;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (SIZE_MAX);
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		if (res > SIZE_MAX / 10
			|| (res == SIZE_MAX / 10 && (str[i] - '0') > SIZE_MAX % 10))
			return (SIZE_MAX);
		res = 10 * res + (str[i++] - '0');
	}
	return (res);
}

int	syntax_error(int ac, char **av)
{
	int		num;
	char	**temp;

	temp = av;
	if (!(ac == 5 || ac == 6))
		return (printf("\033[0;31mERROR! give 5 or 6 args.\n\033[0m"), 1);
	while (*++temp)
	{
		num = ft_atoi(*temp);
		if (num == 0)
			return (printf("ERROR! argument can't be zero\n"), 1);
	}
	if (ft_atoi(av[1]) < 2)
		return (printf("Error! Invalid philosopher count RTFM!\n"), 1);
	if (ft_atoi(av[2]) < 60)
		return (printf("Error! Invalid time to die RTFM!\n"), 1);
	if (ft_atoi(av[3]) < 60)
		return (printf("Error! Invalid time to eat RTFM!\n"), 1);
	if (ft_atoi(av[4]) < 60)
		return (printf("Error! Invalid time to sleep RTFM!\n"), 1);
	if (ac == 6 && ft_atoi(av[5]) < 0)
		return (printf("Error! Invalid eat count RTFM!\n"), 1);
	return (printf("No syntax errors found\n"), 0);
}
