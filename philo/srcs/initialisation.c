/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:26:34 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/31 15:48:28 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	inittime(t_simulation *sim)
{
	struct timeval	st;
	unsigned int	i;

	if (gettimeofday(&st, NULL) == 1)
		return (write(2, "Error in getting start time\n", 27), 1);
	sim->start = gettimeinms();
	i = -1;
	while (++i, i < sim->nbp)
		sim->philo[i]->start = sim->start;
	return (0);
}

unsigned int	maxf(unsigned int nbp, unsigned int o)
{
	if (o == 0)
		return (nbp - 1);
	else
		return (o - 1);
}

static int	initfork(unsigned int nbp, t_simulation *sm)
{
	unsigned int	o;

	o = -1;
	sm->forks = malloc(sizeof(t_forks *) * (nbp + 1));
	if (sm->forks == NULL)
		return (1);
	while (++o, o < nbp)
	{
		sm->forks[o] = (t_forks *)malloc(sizeof(t_forks));
		if (!sm->forks[o])
			return (clean_philo_mem(sm), write(2, "\nenomem\n", 8), 1);
		sm->forks[o]->is_taken = FALSE;
	}
	sm->forks[o] = NULL;
	o = -1;
	while (++o, o < nbp)
	{
		sm->philo[o]->forkg = sm->forks[o];
		if (nbp != 1)
			sm->philo[o]->forkd = sm->forks[maxf(nbp, o)];
	}
	o = -1;
	while (++o, o < nbp)
		pthread_mutex_init(&sm->forks[o]->fork, NULL);
	return (0);
}

int	initsim(char **v, t_simulation *sim)
{
	sim->nbp = atoiunsigned(*(v + 1));
	if (sim->nbp > INT_MAX || sim->nbp == 0)
		return (0);
	sim->ttd = atoiunsigned(*(v + 2));
	if (sim->ttd > INT_MAX)
		return (0);
	sim->tte = atoiunsigned(*(v + 3));
	if (sim->nbp > INT_MAX)
		return (0);
	sim->tts = atoiunsigned(*(v + 4));
	if (sim->nbp > INT_MAX)
		return (0);
	if (*(v + 5) != NULL)
	{
		sim->nbm = atoiunsigned(*(v + 5));
		if (sim->nbm > INT_MAX)
			return (0);
	}
	else
		sim->nbm = -1;
	sim->is_on = TRUE;
	return (1);
}

int	initphilo(t_simulation *sim)
{
	unsigned int	o;

	o = -1;
	sim->philo = NULL;
	sim->forks = NULL;
	sim->philo = (t_philo **)malloc(sizeof(t_philo *) * (sim->nbp + 1));
	if (sim->philo == NULL)
		return (clean_philo_mem(sim), 1);
	while (++o, o < sim->nbp)
	{
		sim->philo[o] = (t_philo *)malloc(sizeof(t_philo));
		if (!sim->philo[o])
			return (clean_philo_mem(sim), 1);
		sim->philo[o]->num = o;
		sim->philo[o]->last_meal = 0;
		sim->philo[o]->meals = 0;
		sim->philo[o]->ttt = 0;
		sim->philo[o]->tte = sim->tte;
		sim->philo[o]->ttd = sim->ttd;
		sim->philo[o]->tts = sim->tts;
		sim->philo[o]->nbm = sim->nbm;
		sim->philo[o]->nbp = sim->nbp;
	}
	sim->philo[o] = NULL;
	return (initfork(sim->nbp, sim));
}
