/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:25:30 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/24 00:52:22 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_simulation *sm)
{
	time_t	wake_time;

	wake_time = gettimeinms() + sm->tts;
	while (gettimeinms() < wake_time)
	{
		if (sm->is_on == FALSE)
			break ;
		usleep(10);
	}
}

void	die(t_simulation *sm)
{
	time_t	die_time;

	die_time = gettimeinms() + sm->ttd;
	while (gettimeinms() < die_time)
	{
		usleep(100);
	}
	printf("%ld: %d died\n", gettimeinms() - sm->start, sm->philo[0]->num);
	sm->is_on = FALSE;
}

void	*thread_routine_one(void *a)
{
	t_simulation	*sm;

	sm = (t_simulation *)a;
	if (sm->forks[0]->is_taken == FALSE)
	{
		pthread_mutex_lock(&sm->forks[0]->fork);
		printf("%ld: %d has taken a fork\n", gettimeinms() - sm->start,
			sm->philo[0]->num);
		sm->forks[0]->is_taken = TRUE;
	}
	die(sm);
	pthread_mutex_unlock(&sm->forks[0]->fork);
	sm->forks[0]->is_taken = FALSE;
	return (NULL);
}

void	diner_one(t_simulation *b)
{
	pthread_create(&b->philo[0]->name, NULL, thread_routine_one, b);
	pthread_join(b->philo[0]->name, NULL);
}

void	*diner(void *a)
{
	t_simulation	*b;

	b = (t_simulation *)a;
	if (inittime(b) == 1)
		return (NULL);
	if (b->nbp == 1)
	{
		diner_one(b);
		return (b->is_on = FALSE, NULL);
	}
	return (NULL);
}
