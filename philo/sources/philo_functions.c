/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:21:19 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/29 02:17:20 by mlindenm         ###   ########.fr       */
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

int	print_helper(char *msg, long int arg1, int arg2)
{
	if (!dead())
	{
		pthread_mutex_lock(&get_d()->m_print);
		printf(msg, arg1, arg2);
		pthread_mutex_unlock(&get_d()->m_print);
		return (0);
	}
	else
		return (1);
}

void	think(t_p *p)
{
	print_helper("%ld %d is thinking\n", get_time() - get_d()->start_time, p->number);
	// ft_usleep(d.time_to_eat / 5);
}

void	do_sleep(t_p *p)
{
	print_helper("%ld %d is sleeping\n", get_time() - get_d()->start_time, p->number);
	// usleep(d.time_to_sleep * 1000);
	ft_usleep(get_d()->time_to_sleep);
}

void	eat(t_p *p)
{
	pthread_mutex_lock(p->left_fork->m_fork);
	// pthread_mutex_lock(&get_d()->m_print);
	// printf("left fork: %p with number: %d\n", p->left_fork->m_fork, p->left_fork->number);
	// pthread_mutex_unlock(&get_d()->m_print);

	if (print_helper("%ld %d has taken a fork\n", get_time() - get_d()->start_time, p->number))
	{
		pthread_mutex_unlock(p->left_fork->m_fork);
		return ;
	}

	pthread_mutex_lock(p->right_fork->m_fork);
	// pthread_mutex_lock(&get_d()->m_print);
	// printf("right fork: %p with number: %d\n", p->right_fork->m_fork, p->right_fork->number);
	// pthread_mutex_unlock(&get_d()->m_print);

	if (print_helper("%ld %d has taken a fork\n", get_time() - get_d()->start_time, p->number))
	{
		pthread_mutex_unlock(p->left_fork->m_fork);
		pthread_mutex_unlock(p->right_fork->m_fork);
		return ;
	}

	pthread_mutex_lock(&get_d()->m_last_meal);
	// pthread_mutex_lock(&get_d()->m_print);
	// printf("last meal: %p\n", (long int *)(p->last_meal_time));
	// pthread_mutex_unlock(&get_d()->m_print);
	p->last_meal_time = (long)get_time() - get_d()->start_time;
	p->meals_eaten++;
	pthread_mutex_unlock(&get_d()->m_last_meal);

	if (print_helper("%ld %d is eating\n", get_time() - get_d()->start_time, p->number))
	{
		pthread_mutex_unlock(p->left_fork->m_fork);
		pthread_mutex_unlock(p->right_fork->m_fork);
		return ;
	}

	// usleep(d.time_to_eat * 1000);
	ft_usleep(get_d()->time_to_eat);
	pthread_mutex_unlock(p->left_fork->m_fork);
	pthread_mutex_unlock(p->right_fork->m_fork);
}
