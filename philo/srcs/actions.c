/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:04:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/03 18:53:41 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_simu(t_philo *p)
{
	pthread_mutex_lock(&p->mutex[CHECK_DONE]);
	if (*(p->on) == FALSE)
	{
		pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
		return (FALSE);
	}
	pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
	return (TRUE);
}

void	sleeping(t_philo *p)
{
	time_t	wake_time;
	time_t	lim;

	wake_time = gettimeinms() + p->tte;
	lim = gettimeinms() + p->ttd;
	pthread_mutex_lock(&p->mutex[PRINT]);
	printf("%ld %d is sleeping\n", gettimeinms() - p->start, p->num + 1);
	pthread_mutex_unlock(&p->mutex[PRINT]);
	if (wake_time > lim)
	{
		while (gettimeinms() < lim)
			usleep(10);
		pthread_mutex_lock(&p->mutex[CHECK_DONE]);
		*(p->on) = FALSE;
		pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
		pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
		p->tod = gettimeinms();
		pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
		return ;
	}
	while (gettimeinms() < wake_time)
		usleep(10);
}

void	eat(t_philo *p)
{
	time_t	eat_time;
	time_t	lim;

	eat_time = gettimeinms() + p->tte;
	lim = gettimeinms() + p->ttd;
	pthread_mutex_lock(&p->mutex[PRINT]);
	printf("%ld %d is eating\n", gettimeinms() - p->start, p->num + 1);
	pthread_mutex_unlock(&p->mutex[PRINT]);
	if (eat_time > lim)
	{
		while (gettimeinms() < lim)
			usleep(10);
		pthread_mutex_lock(&p->mutex[CHECK_DONE]);
		*(p->on) = FALSE;
		pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
		pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
		p->tod = gettimeinms();
		return (pthread_mutex_unlock(&p->mutex[CHECK_STATUS]), (void)0);
	}
	while (gettimeinms() < eat_time)
		usleep(10);
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	p->meals++;
	p->last_meal = gettimeinms();
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
}
