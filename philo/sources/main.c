/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:14:50 by mlindenm          #+#    #+#             */
/*   Updated: 2023/06/12 22:50:28 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h> //malloc();

pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	int	i;
	int	mails;

	mails = *(int *)arg;
	i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	printf("mails: %d\n", mails);
	*(int *)arg = mails;
	return (arg);
}

int	main(void)
{
	pthread_t	th[8];
	int			i;
	int			*mails;

	i = 0;
	mails = (int *)malloc(sizeof(int));
	*mails = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 8)
	{
		if (pthread_create(th + i, NULL, &routine, mails) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		printf("Thread %d has started\n", i++);
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(th[i], (void **) &mails) != 0)
			return (2);
		printf("Thread %d has finished execution\n", i++);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", *mails);
	return (0);
}
