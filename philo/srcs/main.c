/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:25:34 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/01 21:04:20 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	argerror(void)
{
	printf(WHITE"Usage: \ntime unit in ms, pos numbers, int max top\n./philo ["
		UNDERLINE_WHITE"NB OF PHILOSOPHERS"WHITE"] ["UNDERLINE_WHITE
		"TIME TO DIE"WHITE"] ["UNDERLINE_WHITE"TIME TO EAT"WHITE"] ["
		UNDERLINE_WHITE	"TIME TO SLEEP"WHITE"] ["UNDERLINE_WHITE
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

static int	initphilo(char **v, t_philo	*philo)
{
	philo->nbp = atoiunsigned(*(v + 1));
	if (philo->nbp > INT_MAX)
		return (0);
	philo->ttd = atoiunsigned(*(v + 2));
	if (philo->ttd > INT_MAX)
		return (0);
	philo->tte = atoiunsigned(*(v + 3));
	if (philo->nbp > INT_MAX)
		return (0);
	philo->tts = atoiunsigned(*(v + 4));
	if (philo->nbp > INT_MAX)
		return (0);
	if (*(v + 5) != NULL)
	{
		philo->nbm = atoiunsigned(*(v + 5));
		if (philo->nbm > INT_MAX)
			return (0);
	}
	else
		philo->nbm = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	philo;	

	if (argc < 5 || argc > 6 || !ft_v_args(argv) || !initphilo(argv, &philo))
		argerror();
	else if (argc == 5)
	{
		// do 5
	}
	else
	{
		// do 6
	}
	return (0);
}
