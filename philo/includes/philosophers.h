/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:56:16 by tnoulens          #+#    #+#             */
/*   Updated: 2022/11/03 20:03:29 by tnoulens         ###   ########.fr       */
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
	dead,
	pense,
	mange,
	dort,
	take,
	done
}	t_status;

typedef enum e_mutex
{
	PRINT,
	CHECK_MEALS,
	CHECK_STATUS,
	CHECK_DONE,
	NB_MUTEX
}	t_mutex;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			is_taken;
}	t_forks;

typedef struct s_philo
{
	pthread_t		name;
	int				num;
	time_t			tod;
	time_t			last_meal;
	unsigned int	meals;
	t_forks			*forkd;
	t_forks			*forkg;
	time_t			ttd;
	time_t			tts;
	time_t			tte;
	time_t			ttt;
	int				nbm;
	unsigned int	nbp;
	time_t			start;
	pthread_mutex_t	*mutex;
	bool			*on;
}	t_philo;

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
	bool			is_done;
	time_t			start;
	pthread_mutex_t	*mutex;
}	t_simulation;

/* --- protoypes --- */

	// initialisation
int				initsim(char **v, t_simulation *sim);
int				initphilo(t_simulation *sim);
int				inittime(t_simulation *sim);

	// actions
int				simulation(t_simulation *b);
void			sleeping(t_philo *p);
void			eat(t_philo *p);
void			*thread_routine_one(void *a);
int				diner_one(t_philo *b);
void			die(t_philo *p);
int				check_simu(t_philo *p);

	// cleaning
void			clean_philo_mem(t_simulation *sm);
void			destroy_fork(t_simulation *sm, int nbp);

	// utilities
unsigned int	atoiunsigned(const char *p);
size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);
void			ft_printab(char **str);
void			ft_print(t_philo *p, t_status action);

	// time utilities
time_t			gettimeinms(void);
unsigned long	multiply_bitewise(long a, long b);

#endif
