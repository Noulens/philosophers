/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:04:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/02 18:38:42 by tnoulens         ###   ########.fr       */
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

	pthread_mutex_lock(&p->mutex[PRINT]);
	wake_time = gettimeinms() + p->tts;
	printf("%ld %d is sleeping\n", gettimeinms() - p->start, p->num + 1);
	pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
	p->status = dort;
	pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
	pthread_mutex_lock(&p->mutex[PRINT]);
	while (gettimeinms() < wake_time)
	{
		usleep(10);
	}
}

void	eat(t_philo *p)
{
	time_t	eat_time;

	pthread_mutex_lock(&p->mutex[PRINT]);
	eat_time = gettimeinms() + p->tte;
	printf("%ld %d is eating\n", gettimeinms() - p->start, p->num + 1);
	pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
	p->status = mange;
	pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	p->meals++;
	p->last_meal = gettimeinms() - p->start;
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
	pthread_mutex_unlock(&p->mutex[PRINT]);
	while (gettimeinms() < eat_time)
	{
		usleep(10);
	}
}
