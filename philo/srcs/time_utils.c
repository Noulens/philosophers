/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:10:43 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/09 16:29:32 by waxxy            ###   ########.fr       */
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
