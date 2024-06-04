/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:41:25 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/05 00:28:50 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = -1;
	if ((str[++i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i++] == '-')
		sign = -1;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		if (res > INT_MAX / 10 || (res == INT_MAX / 10 && str[i]
				- '0' > INT_MAX % 10))
		{
			if (sign == -1)
				return (INT_MIN);
			return (INT_MAX);
		}
		res = 10 * res + (str[i++] - '0');
	}
	return (res * sign);
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
