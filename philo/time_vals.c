/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_vals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:48:17 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/20 06:38:14 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// gives time in milliseconds

size_t	get_curr_time(void)
{
	struct timeval	time;

	// gets the current time in
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//  struct timeval {
//          time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
//          suseconds_t  tv_usec;  /* and microseconds */
//  };

//  struct timezone {
//          int     tz_minuteswest; /* of Greenwich */
//          int     tz_dsttime;     /* type of dst correction to apply */
//  };
