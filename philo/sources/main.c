/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:14:50 by mlindenm          #+#    #+#             */
/*   Updated: 2023/06/10 13:31:15 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void*	routine()
{
	printf("Test\n");
	usleep(1000000);
	printf("Ending\n");
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (0);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (0);
	if (pthread_join(t1, NULL) != 0)
		return (0);
	if (pthread_join(t2, NULL) != 0)
		return (0);
	// write(1,"philo\n", 6);
	return (0);
}
