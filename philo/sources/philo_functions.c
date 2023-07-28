/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:21:19 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/28 20:28:38 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	dead(void)
{
	if (get_d()->death == 1)
		return (1);
	return (0);
}

void	think(t_p *p, t_data d)
{
	pthread_mutex_lock(&d.m_print);
	printf("%ld ms %d is thinking\n", get_time() - d.start_time, p->number);
	pthread_mutex_unlock(&d.m_print);
	usleep(50);
}

void	do_sleep(t_p *p, t_data d)
{
	pthread_mutex_lock(&d.m_print);
	printf("%ld ms %d is sleeping\n", get_time() - d.start_time, p->number);
	pthread_mutex_unlock(&d.m_print);
	usleep(d.time_to_sleep * 1000);
}

void	eat(t_p *p, t_data d)
{
	// dead();
	if (p->number % 2 == 0 && get_time())
		usleep(d.time_to_eat * 1000);
	pthread_mutex_lock(p->left_fork->m_fork);
	// pthread_mutex_lock(&d.m_print);
	printf("%ld ms %d has taken a fork %d\n", get_time() - d.start_time, p->number, p->left_fork->number);
	// pthread_mutex_unlock(&d.m_print);
	pthread_mutex_lock(p->right_fork->m_fork);
	// dead();
	// pthread_mutex_lock(&d.m_print);
	printf("%ld ms %d has taken a fork %d\n", get_time() - d.start_time, p->number, p->right_fork->number);
	printf("%ld ms %d is eating\n", get_time() - d.start_time, p->number);
	// pthread_mutex_unlock(&d.m_print);
	// pthread_mutex_lock(&d.m_last_meal);
	gettimeofday(&p->last_meal_time, NULL);
	// pthread_mutex_unlock(&d.m_last_meal);
	usleep(d.time_to_eat * 1000);
	// pthread_mutex_lock(&d.m_last_meal);
	gettimeofday(&p->last_meal_time, NULL);
	// pthread_mutex_unlock(&d.m_last_meal);
	p->meals_eaten++;
	pthread_mutex_unlock(p->right_fork->m_fork);
	// usleep(50);
	pthread_mutex_unlock(p->left_fork->m_fork);
}
