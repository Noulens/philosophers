/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:04:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/04 16:45:33 by tnoulens         ###   ########.fr       */
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

unsigned int	ttt(t_philo *p)
{
	return (gettimeinms());
}

void	sleeping(t_philo *p)
{
	time_t	wake_time;
	time_t	lim;

	wake_time = gettimeinms() + p->tts;
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	lim = p->last_meal + p->ttd;
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
	ft_print(p, dort);
	if (wake_time > lim)
	{
		while (gettimeinms() < lim)
			usleep(100);
		pthread_mutex_lock(&p->mutex[CHECK_DONE]);
		*(p->on) = FALSE;
		pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
		pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
		p->tod = gettimeinms();
		pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
		return ;
	}
	while (gettimeinms() < wake_time)
		usleep(100);
}

void	eating(t_philo *p)
{
	time_t	eat_time;
	time_t	lim;

	eat_time = gettimeinms() + p->tte;
	lim = gettimeinms() + p->ttd;
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	p->meals++;
	if (p->nbm != -1 && (int)p->meals == p->nbm)
		p->done = TRUE;
	p->last_meal = gettimeinms();
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
	ft_print(p, mange);
	if (eat_time > lim)
	{
		while (gettimeinms() < lim)
			usleep(100);
		pthread_mutex_lock(&p->mutex[CHECK_DONE]);
		*(p->on) = FALSE;
		pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
		pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
		p->tod = gettimeinms();
		return (pthread_mutex_unlock(&p->mutex[CHECK_STATUS]), (void)0);
	}
	while (gettimeinms() < eat_time)
		usleep(100);
}

void	thinking(t_philo *p)
{
	time_t	think_time;
	time_t	lim;

	think_time = gettimeinms() + p->ttt;
	pthread_mutex_lock(&p->mutex[CHECK_MEALS]);
	lim = p->last_meal + p->ttd;
	pthread_mutex_unlock(&p->mutex[CHECK_MEALS]);
	ft_print(p, pense);
	if (think_time > lim)
	{
		while (gettimeinms() < lim)
			usleep(100);
		pthread_mutex_lock(&p->mutex[CHECK_DONE]);
		*(p->on) = FALSE;
		pthread_mutex_unlock(&p->mutex[CHECK_DONE]);
		pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
		p->tod = gettimeinms();
		return (pthread_mutex_unlock(&p->mutex[CHECK_STATUS]), (void)0);
	}
	while (gettimeinms() < think_time)
		usleep(100);
}
