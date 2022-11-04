/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:25:34 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/04 16:37:21 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	argerror(void)
{
	printf(WHITE"Usage: \ntime unit in ms, pos numbers, int max top\n./philo ["
		UNDERLINE_WHITE"NB OF PHILOSOPHERS"WHITE"] ["UNDERLINE_WHITE
		"TIME TO DIE"WHITE"] ["UNDERLINE_WHITE"TIME TO EAT"WHITE"] ["
		UNDERLINE_WHITE"TIME TO SLEEP"WHITE"] ["UNDERLINE_WHITE
		"optional NUMBER OF MEAL"RESET"]\n");
}

static int	ft_checkint(char **p)
{
	int	res;

	res = 0;
	while (p[res])
	{
		if (ft_strlen(p[res]) > 10)
			return (0);
		res++;
	}
	return (1);
}

static int	ft_v_args(char **v)
{
	int	i;
	int	j;
	int	sign;

	i = 0;
	while (v[++i])
	{
		j = -1;
		sign = 0;
		while (v[i][++j])
		{
			if (v[i][j] == '+' && sign == 0)
			{
				sign++;
				if (!ft_isdigit(v[i][j + 1]))
					return (0);
			}
			else if (!ft_isdigit(v[i][j]))
				return (0);
		}
	}
	if (!ft_checkint(v + 1))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	sm;

	if (argc < 5 || argc > 6 || !ft_v_args(argv) || !initsim(argv, &sm))
		argerror();
	else
	{
		if (initphilo(&sm, -1) == 1)
			return (write(2, "enomem\n", 7), 1);
		if (simulation(&sm) != SUCCES)
			write(2, "failed\n", 7);
		destroy_fork(&sm, sm.nbp);
		clean_philo_mem(&sm);
	}
	return (0);
}

/* 		for (unsigned int i = 0; i < sm.nbp; i++)
		{
			printf("addr philo g: %p\naddr simul g: %p\n\naddr philo d: %p\n\n"
			, &sm.philo[i]->forkg->fork, &sm.forks[i]->fork,
			&sm.philo[i]->forkd->fork);
		}		*/
