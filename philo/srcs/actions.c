/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:25:30 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/23 20:29:25 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*diner(void *a)
{
	t_simulation	*b;
	struct timeval	itg;

	b = (t_simulation *)a;
	if (inittime(b) == 1)
		return ;
}

void	sleeping(t_simulation *sm)
{
	time_t	wake_time;

	wake_time = gettimeinms() + sm->tts;
	while (gettimeinms() < wake_time)
	{
		if (sm->is_on == FALSE)
			break ;
		usleep(10);
	}
}
