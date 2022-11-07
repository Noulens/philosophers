/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:34:09 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/03 19:57:18 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_philo_mem(t_simulation *sm)
{
	int	o;

	o = -1;
	if (sm->philo != NULL)
	{
		while (sm->philo[++o] != NULL)
			free(sm->philo[o]);
		free(sm->philo);
	}
	o = -1;
	if (sm->forks != NULL)
	{
		while (sm->forks[++o] != NULL)
			free(sm->forks[o]);
		free(sm->forks);
	}
	o = -1;
	if (sm->mutex != NULL)
	{
		free(sm->mutex);
	}
}

void	destroy_fork(t_simulation *sm, int nbp)
{
	int	o;

	o = -1;
	while (++o, o < nbp)
		if (pthread_mutex_destroy(&sm->forks[o]->fork) == EBUSY)
			printf("Fork mutex [%u] is busy and was not destroyed\n", o);
	o = -1;
	while (++o, o < NB_MUTEX)
		if (pthread_mutex_destroy(&sm->mutex[o]) == EBUSY)
			printf("Mutex [%u] is busy and was not destroyed\n", o);
}
