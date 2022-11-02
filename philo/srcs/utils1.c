/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:00:01 by waxxy             #+#    #+#             */
/*   Updated: 2022/11/02 08:55:31 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	atoiunsigned(const char *p)
{
	unsigned int	result;
	const char		*nptr;

	nptr = p;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		++nptr;
	if (*nptr == '+')
	{
		++nptr;
	}
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - 48;
		++nptr;
	}
	return (result);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		++i;
	return (i);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_printab(char **str)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
		{
			printf("%s\n", str[i]);
			i++;
		}
	}
}

void	ft_print(t_philo *p, t_status action)
{
	if (action == mange)
		printf("%ld %d is sleeping", gettimeinms() - p->start, p->num + 1);
	else if (action == pense)
		printf("%ld %d is thinking", gettimeinms() - p->start, p->num + 1);
	else if (action == dort)
		printf("%ld %d is eating", gettimeinms() - p->start, p->num + 1);
	else if (action == pepsi)
		printf("%ld %d died", gettimeinms() - p->start, p->num + 1);
}
