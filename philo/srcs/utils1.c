/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:00:01 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/23 22:10:32 by tnoulens         ###   ########.fr       */
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	register void	*p;
	register char	*ptr;
	register size_t	mem_size;
	register size_t	max_st;

	max_st = ~(size_t)0;
	if (size > 0 && nmemb > max_st / size)
		return (NULL);
	mem_size = nmemb * size;
	p = malloc(mem_size);
	if (!p)
		return (NULL);
	ptr = p;
	while (mem_size--)
		*ptr++ = '\0';
	return (p);
}
