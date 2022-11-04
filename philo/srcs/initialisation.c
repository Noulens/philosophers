/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:26:34 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/04 16:39:17 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	inittime(t_simulation *sim)
{
	unsigned int	i;

	sim->start = gettimeinms();
	i = -1;
	while (++i, i < sim->nbp)
		sim->philo[i]->start = sim->start;
	return (0);
}

static int	initfork(int o, unsigned int nbp, t_simulation *sm)
{
	sm->forks = malloc(sizeof(t_forks *) * (nbp + 1));
	if (sm->forks == NULL)
		return (1);
	while (--o, o >= 0)
	{
		sm->forks[o] = (t_forks *)malloc(sizeof(t_forks));
		if (!sm->forks[o])
			return (clean_philo_mem(sm), write(2, "\nenomem\n", 8), 1);
	}
	sm->forks[nbp] = NULL;
	while (++o, o < (int)nbp)
	{
		sm->philo[o]->forkg = sm->forks[o];
		if (nbp != 1)
			sm->philo[o]->forkd = sm->forks[(o + 1) % nbp];
		sm->philo[o]->mutex = sm->mutex;
	}
	while (--o, o >= 0)
		pthread_mutex_init(&sm->forks[o]->fork, NULL);
	while (++o, o < NB_MUTEX)
		pthread_mutex_init(&sm->mutex[o], NULL);
	return (0);
}

int	initsim(char **v, t_simulation *sim)
{
	sim->nbp = atoiunsigned(*(v + 1));
	sim->ttd = atoiunsigned(*(v + 2));
	sim->tte = atoiunsigned(*(v + 3));
	sim->tts = atoiunsigned(*(v + 4));
	if (sim->nbp > INT_MAX || sim->nbp == 0 || sim->ttd > INT_MAX
		|| sim->nbp > INT_MAX || sim->nbp > INT_MAX)
		return (0);
	if (*(v + 5) != NULL)
	{
		sim->nbm = atoiunsigned(*(v + 5));
		if ((unsigned int)sim->nbm > INT_MAX || sim->nbm == 0)
			return (0);
	}
	else
		sim->nbm = -1;
	sim->is_on = TRUE;
	sim->mutex = malloc(sizeof(pthread_mutex_t) * NB_MUTEX);
	if (sim->mutex == NULL)
		return (write(2, "enomem\n", 7), 0);
	return (1);
}

int	initphilo(t_simulation *sim, int idx)
{
	sim->forks = NULL;
	sim->philo = (t_philo **)malloc(sizeof(t_philo *) * (sim->nbp + 1));
	if (sim->philo == NULL)
		return (clean_philo_mem(sim), 1);
	while (++idx, idx < (int)sim->nbp)
	{
		sim->philo[idx] = (t_philo *)malloc(sizeof(t_philo));
		if (!sim->philo[idx])
			return (clean_philo_mem(sim), 1);
		sim->philo[idx]->num = idx;
		sim->philo[idx]->meals = 0;
		sim->philo[idx]->last_meal = 0;
		sim->philo[idx]->tod = 0;
		sim->philo[idx]->done = FALSE;
		sim->philo[idx]->tte = sim->tte;
		sim->philo[idx]->ttd = sim->ttd;
		sim->philo[idx]->tts = sim->tts;
		sim->philo[idx]->nbm = sim->nbm;
		sim->philo[idx]->nbp = sim->nbp;
		sim->philo[idx]->on = &sim->is_on;
	}
	sim->philo[idx] = NULL;
	return (initfork((int)sim->nbp, sim->nbp, sim));
}
