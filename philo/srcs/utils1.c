/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:00:01 by waxxy             #+#    #+#             */
/*   Updated: 2022/11/03 20:03:29 by tnoulens         ###   ########.fr       */
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
	pthread_mutex_lock(&p->mutex[PRINT]);
	if (action == take)
		printf("%ld %d has taken a fork\n", gettimeinms() - p->start,
			p->num + 1);
	else if (action == mange)
		printf("%ld %d is sleeping\n", gettimeinms() - p->start, p->num + 1);
	else if (action == pense)
		printf("%ld %d is thinking\n", gettimeinms() - p->start, p->num + 1);
	else if (action == dort)
		printf("%ld %d is eating\n", gettimeinms() - p->start, p->num + 1);
	else if (action == dead)
	{
		pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
		printf("%ld %d died\n", p->tod - p->start, p->num + 1);
		pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
	}
	pthread_mutex_unlock(&p->mutex[PRINT]);
}
