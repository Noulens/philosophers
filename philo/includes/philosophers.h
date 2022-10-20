/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:56:16 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/20 15:50:32 by tnoulens         ###   ########.fr       */
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
# define MM 1000000
# define M 1000

/* --- stuctures --- */

typedef struct s_simulation
{
	unsigned int	ttd;
	unsigned int	tts;
	unsigned int	tte;
	unsigned int	nbm;
	unsigned int	nbp;
	suseconds_t		time;
	suseconds_t		start;
}	t_simulation;

typedef enum e_state
{
	pepsi,
	pense,
	mange,
	dort
}	t_status;

typedef struct s_philo
{
	t_simulation	*sim;
	int				num;
	int				fourchette;
	t_status		status;
}	t_philo;

/* --- protoypes --- */

	// initialisation
int				initsim(char **v, t_simulation *sim, struct timeval *st);
int				initphilo(t_philo **philo, t_simulation *sim);

	// actions
void			*eat(void *a);
void			*is_sleep(void *a);

	// cleaning
void			clean_philo_mem(t_philo **philo);

	// utilities
unsigned int	atoiunsigned(const char *p);
size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);
void			ft_printab(char **str);
unsigned long	multiply_bitewise(long a, long b);
void			*ft_calloc(size_t nmemb, size_t size);

#endif
