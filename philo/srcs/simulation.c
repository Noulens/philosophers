/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:25:30 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/06 15:12:42 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* TO DO : DL à corriger  et implémenter le calcul du ttt changer le init fork 
pour que ca init dans l'ordre croissant */

int	diner_finish(t_simulation *sim, int nbm)
{
	unsigned int	i;
	unsigned int	total;

	if (nbm == -1)
		return (FALSE);
	i = 0;
	total = 0;
	while (i < sim->nbp)
	{
		pthread_mutex_lock(&sim->mutex[CHECK_MEALS]);
		if (sim->philo[i]->done == TRUE)
			total += 1;
		pthread_mutex_unlock(&sim->mutex[CHECK_MEALS]);
		i++;
		usleep(100);
	}
	if (total >= sim->nbp)
	{
		pthread_mutex_lock(&sim->mutex[CHECK_DONE]);
		sim->is_on = FALSE;
		pthread_mutex_unlock(&sim->mutex[CHECK_DONE]);
		return (TRUE);
	}
	return (FALSE);
}

void	monitoring(t_simulation *sim)
{
	int				k;
	unsigned int	meal;
	unsigned int	death;

	k = 0;
	while (TRUE)
	{
		pthread_mutex_lock(&sim->mutex[CHECK_MEALS]);
		meal = sim->philo[k]->last_meal - sim->start;
		pthread_mutex_unlock(&sim->mutex[CHECK_MEALS]);
		pthread_mutex_lock(&sim->mutex[CHECK_STATUS]);
		death = sim->philo[k]->tod;
		pthread_mutex_unlock(&sim->mutex[CHECK_STATUS]);
		if ((meal && diner_finish(sim, sim->nbm) == TRUE))
			break ;
		//if ((gettimeinms() - sim->start + sim->tte) > (meal + sim->ttd))
		//{
		//	pthread_mutex_lock(&sim->mutex[CHECK_STATUS]);
		//	sim->philo[k]->tod = gettimeinms() - sim->start;
		//	pthread_mutex_unlock(&sim->mutex[CHECK_STATUS]);
		//	pthread_mutex_lock(&sim->mutex[CHECK_DONE]);
		//	sim->is_on = FALSE;
		//	pthread_mutex_unlock(&sim->mutex[CHECK_DONE]);
		//}
		if (death)
		{
			ft_print(sim->philo[k], dead);
			break ;
		}
		k = (k + 1) % sim->nbp;
		usleep(100);
	}
}

void	*rout(void *a)
{
	t_philo	*p;

	p = (t_philo *)a;
	if (p->num % 2 != 0)
		usleep(100);
	while (TRUE)
	{
		pthread_mutex_lock(&p->forkg->fork);
		if (check_simu(p))
			ft_print(p, take);
		pthread_mutex_lock(&p->forkd->fork);
		if (check_simu(p))
		{
			ft_print(p, take);
			eating(p);
		}
		pthread_mutex_unlock(&p->forkg->fork);
		pthread_mutex_unlock(&p->forkd->fork);
		if (check_simu(p))
			sleeping(p);
		if (check_simu(p))
			thinking(p);
		else
			break ;
	}
	return (NULL);
}

int	simulation(t_simulation *b, int idx)
{
	if (inittime(b) == 1)
		return (FAIL);
	if (b->nbp == 1)
		return (diner_one(b->philo[0]), b->is_on = FALSE, SUCCES);
	while (++idx, idx < (int)b->nbp)
	{
		if (pthread_create(&b->philo[idx]->name, NULL, rout, b->philo[idx]))
		{
			while (--idx)
				if (pthread_join(b->philo[idx]->name, NULL))
					write(2, "failed to join", 14);
			return (FAIL);
		}
	}
	usleep(100);
	monitoring(b);
	idx = -1;
	while (++idx, idx < (int)b->nbp)
	{
		if (pthread_join(b->philo[idx]->name, NULL))
			write(2, "failed to join at exit", 22);
	}
	return (SUCCES);
}
