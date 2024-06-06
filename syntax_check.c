/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:41:25 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/06 17:24:14 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_atozu(const char *str)
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
		if (res > SIZE_MAX / 10 || (res == SIZE_MAX / 10
				&& (unsigned long)(str[i] - '0') > SIZE_MAX % 10))
			return (SIZE_MAX);
		res = 10 * res + (str[i++] - '0');
	}
	return (res);
}

int	error_in_arg(int ac, char **av)
{
	if (ft_atozu(av[1]) < 2 || ft_atozu(av[1]) > 200)
		return (printf(ERROR "Error! Invalid philosopher count RTFM!\n"), 1);
	if (ft_atozu(av[2]) < 60)
		return (printf(ERROR "Error! Invalid time to die RTFM!\n"), 1);
	if (ft_atozu(av[3]) < 60)
		return (printf(ERROR "Error! Invalid time to eat RTFM!\n"), 1);
	if (ft_atozu(av[4]) < 60)
		return (printf(ERROR "Error! Invalid time to sleep RTFM!\n"), 1);
	if (ac == 6 && ft_atozu(av[5]) < 0)
		return (printf(ERROR "Error! Invalid eat count RTFM!\n"), 1);
	return (0);
}

int	syntax_error(int ac, char **av)
{
	int		num;
	char	*arg;
	char	**temp;

	if (ac != 5 && ac != 6)
		return (printf(ERROR "ERROR! Provide 5 or 6 arguments.\n" RESET), 1);
	temp = av;
	while (*++temp)
	{
		arg = *temp;
		if (!*arg)
			return (printf(ERROR "ERROR! Argument can't be empty.\n" RESET), 1);
		while (*arg)
		{
			if (*arg < '0' || *arg > '9')
				return (printf(ERROR "ERROR! Numeric args needed.\n" RESET), 1);
			arg++;
		}
		num = ft_atozu(*temp);
		if (num == 0 || num == SIZE_MAX)
			return (printf(ERROR "ERROR! Argument overflow.\n" RESET), 1);
	}
	if (!error_in_arg(ac, av) && FASAK)
		printf(OUTPUT "-----\t No syntax errors found -----\n" RESET);
	return (0);
}
