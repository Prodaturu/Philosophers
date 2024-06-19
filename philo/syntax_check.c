/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:41:25 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/19 20:55:22 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_atozu(const char *str)
{
	size_t	res;
	int		i;

	res = 0;
	i = 0;

	// check for any leading white spaces and skip them
	// ascii values of white spaces: 32, 9, 10, 11, 12, 13
	// so we check at start if any of these values are present and skip them
	// till we find a valid number or a sign
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;

	// if we encounter a sign first, it could be - or +
	// 1) if '-' sign then we return SIZE_MAX to indicate an error
	// 2) if '+' sign then we skip it and move to the next character
	if (str[i] == '-')
		return (SIZE_MAX);
	else if (str[i] == '+')
		i++;

	// now we start converting the string type number to a size_t number
	// we check if the character is a number and convert it to a number
	// we multiply the previous number by 10 and add the new number to it
	// essentialy increasing the numbers value by 10 times each time it goes left
	// we do this till we reach the end of the string or a non-number character
	// if the number is greater than SIZE_MAX or we encounter a non-digit,
	// 		we return SIZE_MAX to indicate an error
	// if the number is within the range, we return the number
	while (str[i] != '\0')
	{
		// ensures that the character is a number
		// if not, we return SIZE_MAX to indicate an error
		if (str[i] < '0' || str[i] > '9') // If not a digit, return error
            return (SIZE_MAX);

		// If number is more than SIZE_MAX / 10, returns SIZE_MAX to show error
		if (res > SIZE_MAX / 10 || (res == SIZE_MAX / 10
				&& (unsigned long)(str[i] - '0') > SIZE_MAX % 10))
			return (SIZE_MAX);
		res = 10 * res + (str[i++] - '0');
	}
	return (res);
}

/**
 * @brief check if the input arguments are within the handled range
 * @param ac number of arguments
 * @param av arguments
 * @return int; 1 if error, 0 if no error
 * 
 */
int	error_in_arg(int ac, char **av)
{
	// check if the input asks for less than one philo or more than 200 philos
	// 		return an error msg and return true for error in args
	if (ft_atozu(av[1]) < 1 || ft_atozu(av[1]) > 200)
		return (printf(ERROR "Error! Invalid philosopher count!\n" RESET), 1);
	if (ft_atozu(av[2]) < 60)
		return (printf(ERROR "Error! Invalid time to die!\n" RESET), 1);
	if (ft_atozu(av[3]) < 60)
		return (printf(ERROR "Error! Invalid time to eat!\n" RESET), 1);
	if (ft_atozu(av[4]) < 60)
		return (printf(ERROR "Error! Invalid time to sleep!\n" RESET), 1);
	if (ac == 6 && ft_atozu(av[5]) < 0)
		return (printf(ERROR "Error! Invalid eat count!\n" RESET), 1);
	return (0);
}

int	syntax_error(int ac, char **av)
{
	size_t		num;
	char		*arg;
	char		**temp;

	// If there are less or more than the valid num of arguments
		// 	return an error indicating the same and 1
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
	if (error_in_arg(ac, av))
		return (1);
	if (FASAK)
		printf(OUTPUT "\n-----\t No syntax errors found -----\n\n" RESET);
	return (0);
}

/* Deatiled explanation of all functions in the file: */

// The functions in this file are used mainly for two purposes:
// 1. To convert the input strings in argv to size_t integers - ft_atozu
// 2. To check if the input arguments are valid - error_in_arg, syntax_error

/* :: type conversion function */

/* --- ft_atozu --- */
// As our aim is to convert the input arguments to values we can work with,
// we need to chose a data type that can hold the values of the arguments.
// We have chosen size_t as the datatype for mainly 2 reasons:
// 1. size_t can hold large values, which is needed for the time values
// 2. As it only stores positive values, we are not wasting memory 
//	   storing negative values, which we don't need in this case.
// implemenation: explained in the function
