/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:10:43 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/23 20:11:57 by tnoulens         ###   ########.fr       */
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

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * M) + (tv.tv_usec / M));
}
