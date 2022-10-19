/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:25:30 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/11 15:32:41 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eat(void *a)
{
	t_philo			*b;
	struct timeval	itg;

	b = (t_philo *)a;
	gettimeofday(&itg, NULL);
	b->time = (multiply_bitewise(itg.tv_sec, MM) + itg.tv_usec) - b->start;
	printf("%ld %d is eating\n", b->time / M, b->nbp);
	usleep(multiply_bitewise(b->tte, M));
	return (NULL);
}

void	*is_sleep(void *a)
{
	t_philo			*b;
	struct timeval	itg;

	b = (t_philo *)a;
	gettimeofday(&itg, NULL);
	b->time = (multiply_bitewise(itg.tv_sec, MM) + itg.tv_usec) - b->start;
	printf("%ld %d is sleeping\n", b->time / M, b->nbp);
	usleep(multiply_bitewise(b->tts, M));
	return (NULL);
}
