/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:26:34 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/20 15:50:12 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initsim(char **v, t_simulation *sim, struct timeval *st)
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
	gettimeofday(st, NULL);
	sim->start = multiply_bitewise(st->tv_sec, MM) + st->tv_usec;
	return (1);
}

int	initphilo(t_philo **philo, t_simulation *sim)
{
	unsigned int	o;

	o = -1;
	while (++o, o < sim->nbp)
	{
		philo[o] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[o])
		{
			clean_philo_mem(philo);
			write(2, "\nenomem\n", 8);
			return (1);
		}
		philo[o]->sim = sim;
		philo[o]->num = o + 1;
		philo[o]->fourchette = o;
	}
	return (0);
}
