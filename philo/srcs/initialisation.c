/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:26:34 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/23 21:27:07 by tnoulens         ###   ########.fr       */
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

static int	initfork(unsigned int nbp, t_philo **philo, t_forks **fork)
{
	unsigned int	o;

	o = -1;
	fork = (t_forks **)ft_calloc(sizeof(t_forks *), nbp);
	if (fork == NULL)
		return (1);
	while (++o, o < nbp)
	{
		fork[o] = (t_forks *)malloc(sizeof(t_forks));
		if (!fork[o])
		{
			clean_philo_mem(philo, fork);
			write(2, "\nenomem\n", 8);
			return (1);
		}
		fork[o]->is_taken = FALSE;
	}
	o = -1;
	while (++o, o < nbp)
		pthread_mutex_init(&fork[o]->fork, NULL);
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

int	initphilo(t_philo **philo, t_simulation *sim, t_forks **fork)
{
	unsigned int	o;

	o = -1;
	philo = (t_philo **)ft_calloc(sizeof(t_philo *), sim->nbp);
	if (philo == NULL)
		return (clean_philo_mem(philo, fork), 1);
	while (++o, o < sim->nbp)
	{
		philo[o] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[o])
			return (clean_philo_mem(philo, fork), write(2, "enomem\n", 7), 1);
		philo[o]->num = o + 1;
		philo[o]->fourchette = o;
		philo[o]->last_meal = 0;
		philo[o]->meals = 0;
		philo[o]->ttt = 0;
	}
	if (initfork(sim->nbp, philo, fork) == 1)
		return (1);
	sim->philo = philo;
	sim->forks = fork;
	return (0);
}
