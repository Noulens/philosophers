/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:04:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/31 18:31:42 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *p)
{
	time_t	wake_time;

	wake_time = gettimeinms() + p->tts;
	printf("%ld %d is sleeping\n", gettimeinms() - p->start, p->num + 1);
	p->status = dort;
	while (gettimeinms() < wake_time)
	{
		usleep(10);
	}
}

void	eat(t_philo *p)
{
	time_t	eat_time;

	eat_time = gettimeinms() + p->tte;
	printf("%ld %d is eating\n", gettimeinms() - p->start, p->num + 1);
	p->status = mange;
	p->meals++;
	p->last_meal = gettimeinms() - p->start;
	while (gettimeinms() < eat_time)
	{
		usleep(10);
	}
}
