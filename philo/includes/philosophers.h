/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:56:16 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/09 16:25:23 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "colors.h"

/* --- defines --- */

# define TRUE 1
# define FALSE 0
# define SUCCES 0
# define FAIL 1
# define MIL 1000000

/* --- stuctures --- */

typedef struct s_philo
{
	unsigned int	ttd;
	unsigned int	tts;
	unsigned int	tte;
	unsigned int	nbm;
	unsigned int	nbp;
	suseconds_t		time;
	suseconds_t		start;
}	t_philo;

/* --- protoypes --- */

	// utilities
unsigned int	atoiunsigned(const char *p);
size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);
void			ft_printab(char **str);
unsigned long	multiply_bitewise(long a, long b);

#endif
