/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:21:19 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/29 00:38:24 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	dead(void)
{
	pthread_mutex_lock(&get_d()->m_dead);
	if (get_d()->death == 1)
	{
		pthread_mutex_unlock(&get_d()->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&get_d()->m_dead);
	return (0);
}

void	think(t_p *p, t_data d)
{
	pthread_mutex_lock(&d.m_print);
	printf("%ld %d is thinking\n", get_time() - d.start_time, p->number);
	// ft_usleep(d.time_to_eat / 5);
	pthread_mutex_unlock(&d.m_print);
}

void	do_sleep(t_p *p, t_data d)
{
	pthread_mutex_lock(&d.m_print);
	printf("%ld %d is sleeping\n", get_time() - d.start_time, p->number);
	pthread_mutex_unlock(&d.m_print);
	// usleep(d.time_to_sleep * 1000);
	ft_usleep(d.time_to_sleep);
}

void	eat(t_p *p, t_data d)
{
	pthread_mutex_lock(p->left_fork->m_fork);
	pthread_mutex_lock(&d.m_print);
	printf("%ld %d has taken a fork\n", get_time() - d.start_time, p->number);
	pthread_mutex_unlock(&d.m_print);
	pthread_mutex_lock(p->right_fork->m_fork);
	pthread_mutex_lock(&d.m_print);
	printf("%ld %d has taken a fork\n", get_time() - d.start_time, p->number);
	pthread_mutex_unlock(&d.m_print);

	pthread_mutex_lock(&d.m_last_meal);
	p->last_meal_time = (long)get_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&d.m_last_meal);
	pthread_mutex_lock(&d.m_print);
	printf("%ld %d is eating\n", get_time() - d.start_time, p->number);
	pthread_mutex_unlock(&d.m_print);

	// usleep(d.time_to_eat * 1000);
	ft_usleep(d.time_to_eat);
	pthread_mutex_unlock(p->left_fork->m_fork);
	pthread_mutex_unlock(p->right_fork->m_fork);
}
