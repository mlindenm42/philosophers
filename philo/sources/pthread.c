/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:14:42 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/28 20:20:29 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	*get_d(void)
{
	static t_data	all_t_data;

	return (&all_t_data);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	*p_thread(void *arg)
{
	t_p	*p;

	p = (t_p *)arg;
	while (1)
	{
		if (dead())
			break ;
		eat(p, *get_d());
		if (get_d()->have_to_eat > 0)
		{
			if (p->meals_eaten >= get_d()->have_to_eat)
			{
				pthread_mutex_lock(&get_d()->m_finished);
				get_d()->finished++;
				pthread_mutex_unlock(&get_d()->m_finished);
				break ;
			}
		}
		do_sleep(p, *get_d());
		think(p, *get_d());
	}
	return (NULL);
}
