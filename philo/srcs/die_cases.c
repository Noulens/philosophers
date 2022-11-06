/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_cases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:13:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/06 15:11:25 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	diethinking(t_philo *p, time_t *lim)
{
	while (gettimeinms() < *lim)
		usleep(100);
	pthread_mutex_lock(&p->mutex[CHECK_DONE]);
	*(p->on) = FALSE;
	pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
	pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
	p->tod = gettimeinms() - p->start;
	pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
}

void    dieeating(t_philo *p, time_t *lim)
{
	while (gettimeinms() < *lim)
		usleep(100);
	pthread_mutex_lock(&p->mutex[CHECK_DONE]);
	*(p->on) = FALSE;
	pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
	pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
	p->tod = gettimeinms() - p->start;
	pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
}

void    diesleeping(t_philo *p, time_t *lim)
{
	while (gettimeinms() < *lim)
		usleep(100);
	pthread_mutex_lock(&p->mutex[CHECK_DONE]);
	*(p->on) = FALSE;
	pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
	pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
	p->tod = gettimeinms() - p->start;
	pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
}
