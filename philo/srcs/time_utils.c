/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:10:43 by waxxy             #+#    #+#             */
/*   Updated: 2022/11/04 16:52:24 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	multiply_bitewise(long a, long b)
{
	unsigned long	result;

	result = 0;
	while (b > 0)
	{
		if ((b & 1) == 1)
			result += a;
		b >>= 1;
		a <<= 1;
	}
	return (result);
}

time_t	gettimeinms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 1)
		return (write(2, "Error in getting start time\n", 27), 1);
	return (multiply_bitewise(tv.tv_sec, M) + (tv.tv_usec / M));
}
