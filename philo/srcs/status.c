/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:04:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/06 14:54:41 by tnoulens         ###   ########.fr       */
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
	usleep(10);
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	if (p->done == TRUE)
	{
		pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
		return (FALSE);
	}
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
	return (TRUE);
}

void	sleeping(t_philo *p)
{
	time_t	wake_time;
	time_t	lim;

	getlimsleep(p, &lim, &wake_time);
	ft_print(p, dort);
	if (wake_time > lim)
	{
		diesleeping(p, &lim);
		return ;
	}
	while (gettimeinms() < wake_time)
		usleep(100);
}

void	eating(t_philo *p)
{
	time_t	eat_time;
	time_t	lim;

	if (getlimeat(p, &lim, &eat_time))
		return ;
	ft_print(p, mange);
	if (eat_time > lim)
	{
		dieeating(p, &lim);
		return ;
	}
	while (gettimeinms() < eat_time)
		usleep(100);
}

void	thinking(t_philo *p)
{
	time_t	think_time;
	time_t	lim;

	getlimthink(p, &lim, &think_time);
	ft_print(p, pense);
	if (think_time > lim)
	{
		diethinking(p, &lim);
		return ;
	}
	while (gettimeinms() < think_time)
		usleep(100);
}
