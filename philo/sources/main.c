/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:14:50 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/28 06:31:31 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	*get_d(void)
{
	static t_data	all_t_data;

	return (&all_t_data);
}

void	think(t_p *p, t_data d)
{
	pthread_mutex_lock(&d.m_print);
	printf("%ld ms %d is thinking\n", get_time() - d.start_time, p->number);
	pthread_mutex_unlock(&d.m_print);
	usleep(10);
}

void	eat(t_p *p, t_data d)
{
	if (d.nb_of_ps % p->number == 1)
	{
		if (!pthread_mutex_lock(p->left_fork->m_fork))
		{
			pthread_mutex_lock(&d.m_print);
			printf("%ld ms %d has taken a lfork\n", get_time() - d.start_time, p->number);
			pthread_mutex_unlock(&d.m_print);
			pthread_mutex_lock(p->right_fork->m_fork);
			pthread_mutex_lock(&d.m_print);
			printf("%ld ms %d has taken a rfork\n", get_time() - d.start_time, p->number);
			printf("%ld ms %d is eating\n", get_time() - d.start_time, p->number);
			pthread_mutex_unlock(&d.m_print);
			gettimeofday(&p->last_meal_time, NULL);
			usleep(d.time_to_eat * 1000);
			pthread_mutex_unlock(p->right_fork->m_fork);
			pthread_mutex_unlock(p->left_fork->m_fork);
		}
	}
	else
	{
		if (!pthread_mutex_lock(p->right_fork->m_fork))
		{
			pthread_mutex_lock(&d.m_print);
			printf("%ld ms %d has taken a rfork\n", get_time() - d.start_time, p->number);
			pthread_mutex_unlock(&d.m_print);
			pthread_mutex_lock(p->left_fork->m_fork);
			pthread_mutex_lock(&d.m_print);
			printf("%ld ms %d has taken a lfork\n", get_time() - d.start_time, p->number);
			printf("%ld ms %d is eating\n", get_time() - d.start_time, p->number);
			pthread_mutex_unlock(&d.m_print);
			gettimeofday(&p->last_meal_time, NULL);
			usleep(d.time_to_eat * 1000);
			pthread_mutex_unlock(p->left_fork->m_fork);
			pthread_mutex_unlock(p->right_fork->m_fork);
		}
	}

}

void	do_sleep(t_p *p, t_data d)
{
	pthread_mutex_lock(&d.m_print);
	printf("%ld ms %d is sleeping\n", get_time() - d.start_time, p->number);
	pthread_mutex_unlock(&d.m_print);
	usleep(d.time_to_sleep * 1000);
}

void	*p_thread(void *arg)
{
	t_p	*p;

	p = (t_p *)arg;
	// printf("last meal time: %ld\n", (long)p->last_meal_time.tv_sec*1000 + (long)p->last_meal_time.tv_usec/1000);
	// printf("time toooo die: %ld\n", (long)get_time() - d()->time_to_die);
	while ((long)p->last_meal_time.tv_sec*1000 + (long)p->last_meal_time.tv_usec/1000 > get_time() - get_d()->time_to_die)
	{
		// printf("last meal time: %ld\n", (long)p->last_meal_time.tv_sec*1000 + (long)p->last_meal_time.tv_usec/1000);
		// printf("time toooo die: %ld\n", (long)get_time() - d()->time_to_die);
		think(p, *get_d());
		eat(p, *get_d());
		if (get_d()->have_to_eat > 0)
		{
			p->meals_eaten++;
			if (p->meals_eaten >= get_d()->have_to_eat)
				break ;
		}
		do_sleep(p, *get_d());
	}
	error("DEAD\n");
	return (NULL);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

int	main(int argc, char **argv)
{
	int		i;

	check_arg(argc, argv);
	init(argc, argv);

	i = 0;
	while (i < get_d()->nb_of_ps)
	{
		pthread_join(get_d()->ps[i]->thread, NULL);
		// pthread_mutex_destroy(get_d()->forks[i]->m_fork);
		i++;
	}
	free(get_d()->forks);
	return (0);
}

