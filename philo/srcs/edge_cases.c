/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:53:23 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/07 15:18:52 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	die(t_philo *p)
{
	usleep(p->ttd * M);
	pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
	p->tod = gettimeinms() - p->start;
	pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
	ft_print(p, dead);
}

void	*thread_routine_one(void *a)
{
	t_philo	*p;

	p = (t_philo *)a;
	pthread_mutex_lock(&p->forkg->fork);
	ft_print(p, take);
	pthread_mutex_unlock(&p->forkg->fork);
	die(p);
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
