/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:10:43 by waxxy             #+#    #+#             */
/*   Updated: 2022/11/06 14:57:14 by tnoulens         ###   ########.fr       */
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

void	getlimthink(t_philo *p, time_t *lim, time_t *think_time)
{
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	*lim = gettimeinms() + p->last_meal + p->ttd;
	*think_time = (p->ttd - (gettimeinms() - p->last_meal) - p->tte) / 2;
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
	if (*think_time < 0)
		*think_time = gettimeinms();
	else if (*think_time > 550)
		*think_time = 550;
}

bool	getlimeat(t_philo *p, time_t *lim, time_t *eat_time)
{
	*eat_time = gettimeinms() + p->tte;
	*lim = gettimeinms() + p->ttd;
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	p->meals++;
	if (p->nbm != -1 && (int)p->meals == p->nbm)
	{
		p->done = TRUE;
		p->last_meal = gettimeinms();
		pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
		return (TRUE);
	}
	p->last_meal = gettimeinms();
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
	return (FALSE);
}

void	getlimsleep(t_philo *p, time_t *lim, time_t *wake_time)
{
	*wake_time = gettimeinms() + p->tts;
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	*lim = p->last_meal + p->ttd;
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
}
