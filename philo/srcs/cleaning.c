/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:34:09 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/20 14:38:22 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_philo_mem(t_philo **philo)
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
}
