/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:25:30 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/02 15:14:45 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	diner_finish(t_simulation *sim, int nbm)
{
	unsigned int	i;
	unsigned int	total;

	if (nbm == -1)
		return (FALSE);
	while (i < sim->nbp)
	{
		pthread_mutex_lock(&sim->mutex[CHECK_MEALS]);
			total += sim->philo[i]->meals;
		pthread_mutex_unlock(&sim->mutex[CHECK_MEALS]);
		i++;
		usleep(50);
	}
	if (total == nbm * sim->nbp)
	{
		pthread_mutex_lock(&sim->mutex[CHECK_DONE]);
		sim->is_done = TRUE;
		sim->is_on = FALSE;
		pthread_mutex_unlock(&sim->mutex[CHECK_DONE]);
		return (TRUE);
	}
	return (FALSE);
}

void	is_dead(t_philo *p, t_simulation *sim)
{
	pthread_mutex_lock(&sim->mutex[CHECK_STATUS]);
	ft_print(p, pepsi);
	pthread_mutex_unlock(&sim->mutex[CHECK_STATUS]);
	pthread_mutex_lock(&sim->mutex[CHECK_DONE]);
	sim->is_on = FALSE;
	pthread_mutex_unlock(&sim->mutex[CHECK_DONE]);
}

void	monitoring(t_simulation *sim)
{
	int				k;
	unsigned int	meal;

	k = 0;
	while (TRUE)
	{
		pthread_mutex_lock(&sim->mutex[CHECK_MEALS]);
		meal = sim->philo[k]->last_meal;
		pthread_mutex_unlock(&sim->mutex[CHECK_MEALS]);
		if (meal && diner_finish(sim, sim->nbm) == TRUE)
			break ;
		if (meal && gettimeinms() - meal > sim->ttd)
		{
			is_dead(sim->philo[k], sim);
			break ;
		}
		k = (k + 1) % sim->nbp;
		usleep(100);
	}
}

		/* Check if simulation is on */
		/* if even then think */
		/* try to eat */
		/* sleep */
		/* think */

void	*rout(void *a)
{
	t_philo	*p;

	p = (t_philo *)a;
	while (check_simu(p))
	{
		pthread_mutex_lock(&p->forkg->fork);
		printf("%ld %d has taken a fork\n", gettimeinms() - p->start,
			p->num + 1);
		pthread_mutex_lock(&p->forkd->fork);
		printf("%ld %d has taken a fork\n", gettimeinms() - p->start,
			p->num + 1);
		eat(p);
		pthread_mutex_unlock(&p->forkg->fork);
		pthread_mutex_unlock(&p->forkd->fork);
		sleeping(p);
	}
	return (NULL);
}

int	simulation(t_simulation *b)
{
	int	i;

	i = -1;
	if (inittime(b) == 1)
		return (1);
	if (b->nbp == 1)
		return (diner_one(b->philo[0]), b->is_on = FALSE, 0);
	while (++i, i < (int)b->nbp)
	{
		if (pthread_create(&b->philo[i]->name, NULL, rout, b->philo[i]))
		{
			while (--i)
				if (pthread_join(b->philo[i]->name, NULL))
					write(2, "failed to join", 14);
			return (FAIL);
		}
	}
	monitoring(b);
	while (--i)
	{
		pthread_join(b->philo[i]->name, NULL);
	}
	return (SUCCES);
}
