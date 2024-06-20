/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:43:30 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/20 01:42:57 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
	{
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

//  Function to clean up the mutexes and free the philosophers
//  We loop through each philosopher and destroy it's mutexes
void	cleanup_philo(t_philo **philos, int id)
{
	while (id > 0)
	{
		id--;
		pthread_mutex_destroy(&(*philos)[id].r_fork);
		pthread_mutex_destroy(&(*philos)[id].lock_eating);
	}
	free(*philos);
}
