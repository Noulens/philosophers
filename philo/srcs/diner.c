/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:25:30 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/31 16:03:54 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	die(t_philo *p)
{
	time_t	die_time;

	die_time = gettimeinms() + p->ttd;
	while (gettimeinms() < die_time)
	{
		usleep(100);
	}
	printf("%ld: %d died\n", gettimeinms() - p->start, p->num + 1);
}

void	*thread_routine_one(void *a)
{
	t_philo	*p;

	p = (t_philo *)a;
	if (p->forkg->is_taken == FALSE)
	{
		pthread_mutex_lock(&p->forkg->fork);
		printf("%ld: %d has taken a fork\n", gettimeinms() - p->start,
			p->num + 1);
		p->forkg->is_taken = TRUE;
	}
	die(p);
	pthread_mutex_unlock(&p->forkg->fork);
	p->forkg->is_taken = FALSE;
	return (NULL);
}

int	diner_one(t_philo *b)
{
	if (pthread_create(&b->name, NULL, thread_routine_one, b) != 0)
		return (write(2, "error pthread_create one", 24), 1);
	if (pthread_join(b->name, NULL) != 0)
		return (write(2, "error pthread_join one", 22), 1);
	return (0);
}

void	*rout(void *a)
{
	t_philo	*p;

	p = (t_philo *)a;
	if (p->forkg->is_taken == FALSE)
	{
		pthread_mutex_lock(&p->forkg->fork);
		printf("%ld: %d has taken a fork\n", gettimeinms() - p->start,
			p->num + 1);
		p->forkg->is_taken = TRUE;
	}
	die(p);
	pthread_mutex_unlock(&p->forkg->fork);
	p->forkg->is_taken = FALSE;
	return (NULL);
}

int	diner(t_simulation *b)
{
	unsigned int	i;

	i = -1;
	if (inittime(b) == 1)
		return (1);
	if (b->nbp == 1)
		return (diner_one(b->philo[0]), b->is_on = FALSE, 0);
	while (++i, i < b->nbp)
	{
		if (i % 2 != 0)
			pthread_create(&b->philo[i]->name, NULL, rout, b->philo[i]);
		else
		{
			usleep(100);
			pthread_create(&b->philo[i]->name, NULL, rout, b->philo[i]);
		}
	}
	i = -1;
	while (++i, i < b->nbp)
	{
		pthread_join(b->philo[i]->name, NULL);
	}
	return (0);
}
