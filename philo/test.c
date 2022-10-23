/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:28:20 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/23 17:28:35 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#define TIMETC 21000

typedef struct s_counter
{
	pthread_mutex_t	mutex_count;
	unsigned int	count;
}	t_counter;

void	*thread_routine(void *data)
{
	pthread_t		tid;
	t_counter		*counter;
	unsigned int	i;

	tid = pthread_self();
	counter = (t_counter *)data;
	pthread_mutex_lock(&counter->mutex_count);
	printf("Thread [%ld]: au depart = %u.\n", tid, counter->count);
	pthread_mutex_unlock(&counter->mutex_count);
	i = 0;
	while (i < TIMETC)
	{
		pthread_mutex_lock(&counter->mutex_count);
		++counter->count;
		pthread_mutex_unlock(&counter->mutex_count);
		i++;
	}
	pthread_mutex_lock(&counter->mutex_count);
	printf("Thread [%ld]: compte final = %u.\n", tid, counter->count);
	pthread_mutex_unlock(&counter->mutex_count);
	return (NULL);
}

int	main(void)
{
	pthread_t		tid1;
	pthread_t		tid2;
	t_counter		counter;

	counter.count = 0;
	pthread_mutex_init(&counter.mutex_count, NULL);
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("Creation 1er thread:");
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("Creation 2nd thread:");
	pthread_join(tid1, NULL);
	printf("Union 1er thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Union 2nd thread [%ld]\n", tid2);
	if (counter.count != (TIMETC << 1))
		printf("Error ! Expected %d\n", TIMETC << 1);
	else
		printf("OK!\n");
	pthread_mutex_destroy(&counter.mutex_count);
	return (0);
}
