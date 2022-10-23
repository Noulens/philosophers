/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:26:34 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/23 22:21:14 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	inittime(t_simulation *sim)
{
	struct timeval	st;

	if (gettimeofday(&st, NULL) == 1)
		return (write(2, "Error in getting start time\n", 27), 1);
	sim->start = gettimeinms();
	return (0);
}

static int	initfork(unsigned int nbp, t_simulation *sm)
{
	unsigned int	o;

	o = -1;
	sm->forks = malloc(sizeof(t_forks *) * nbp + sizeof(t_forks *));
	if (sm->forks == NULL)
		return (1);
	while (++o, o < nbp)
	{
		sm->forks[o] = (t_forks *)malloc(sizeof(t_forks));
		if (!sm->forks[o])
		{
			clean_philo_mem(sm);
			write(2, "\nenomem\n", 8);
			return (1);
		}
		sm->forks[o]->is_taken = FALSE;
	}
	sm->forks[o] = NULL;
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
		sim->philo[o]->num = o + 1;
		sim->philo[o]->fourchette = o;
		sim->philo[o]->last_meal = 0;
		sim->philo[o]->meals = 0;
		sim->philo[o]->ttt = 0;
	}
	sim->philo[o] = NULL;
	if (initfork(sim->nbp, sim) == 1)
		return (1);
	return (0);
}
