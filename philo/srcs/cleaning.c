/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:34:09 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/23 21:26:58 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_philo_mem(t_philo **philo, t_forks **fork)
{
	int	o;

	o = -1;
	if (philo != NULL)
	{
		while (philo[++o] != NULL)
		{
			free(philo[o]);
		}
		free(philo);
	}
	o = -1;
	if (fork != NULL)
	{
		while (fork[++o] != NULL)
		{
			free(fork[o]);
		}
		free(fork);
	}
}

void	destroy_fork(pthread_mutex_t **fork, int nbp)
{
	unsigned int	o;

	o = -1;
	while (++o, o < nbp)
		if (pthread_mutex_destroy(fork[o]) == EBUSY)
			printf("Mutex [%u] is busy and was not destroyed\n", o);
}
