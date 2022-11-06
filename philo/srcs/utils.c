/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:00:01 by waxxy             #+#    #+#             */
/*   Updated: 2022/11/06 15:14:01 by tnoulens         ###   ########.fr       */
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
		printf(DARK_BLUE"%ld %d has taken a fork\n"RESET, gettimeinms() - p->start,
			p->num + 1);
	else if (action == dort)
		printf(GREEN"%ld %d is sleeping\n"RESET, gettimeinms() - p->start, p->num + 1);
	else if (action == pense)
		printf(RED"%ld %d is thinking\n"RESET, gettimeinms() - p->start, p->num + 1);
	else if (action == mange)
		printf(BLUE"%ld %d is eating\n"RESET, gettimeinms() - p->start, p->num + 1);
	else if (action == dead)
	{
		pthread_mutex_lock(&p->mutex[CHECK_STATUS]);
		printf(YELLOW"%ld %d died\n"RESET, p->tod, p->num + 1);
		pthread_mutex_unlock(&p->mutex[CHECK_STATUS]);
	}
	pthread_mutex_unlock(&p->mutex[PRINT]);
}
