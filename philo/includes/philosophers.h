/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:56:16 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/23 22:28:12 by tnoulens         ###   ########.fr       */
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
# include <stdbool.h>
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
# define C 100

/* --- stuctures --- */

typedef enum e_state
{
	pepsi,
	pense,
	mange,
	dort
}	t_status;

typedef struct s_philo
{
	pthread_t		name;
	int				num;
	int				fourchette;
	t_status		status;
	time_t			last_meal;
	time_t			ttt;
	int				meals;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			is_taken;
}	t_forks;

typedef struct s_simulation
{
	time_t			ttd;
	time_t			tts;
	time_t			tte;
	unsigned int	nbm;
	unsigned int	nbp;
	t_philo			**philo;
	t_forks			**forks;
	bool			is_on;
	time_t			time;
	time_t			start;
}	t_simulation;

/* --- protoypes --- */

	// initialisation
int				initsim(char **v, t_simulation *sim);
int				initphilo(t_simulation *sim);
int				inittime(t_simulation *sim);

	// actions
void			*diner(void *a);
void			sleeping(t_simulation *sm);

	// cleaning
void			clean_philo_mem(t_simulation *sm);
void			destroy_fork(t_simulation *sm, int nbp);

	// utilities
unsigned int	atoiunsigned(const char *p);
size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);
void			ft_printab(char **str);

	// time utilities
time_t			gettimeinms(void);
unsigned long	multiply_bitewise(long a, long b);

#endif
