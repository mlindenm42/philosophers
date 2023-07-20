/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:14:50 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/20 22:13:59 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int				number_of_ps;
// int				time_to_die;
// int				time_to_eat;
// int				time_to_sleep;
// int				number_of_times_each_p_must_eat;
// int				total_meals_eaten;

pthread_mutex_t	*forks;
pthread_mutex_t	output_mutex;

void	think(t_p *p)
{
	printf("%d %d is thinking\n", get_timestamp_ms(), p->number);
	usleep(rand() % 1000);
}

void	eat(t_p *p, t_data d)
{
	printf("%d %d has taken a fork\n", get_timestamp_ms(), p->number);
	pthread_mutex_lock(p->left_fork);
	printf("%d %d has taken a fork\n", get_timestamp_ms(), p->number);
	pthread_mutex_lock(p->right_fork);
	printf("%d %d is eating\n", get_timestamp_ms(), p->number);
	gettimeofday(&p->last_meal_time, NULL);
	usleep(d.time_to_eat * 1000);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	do_sleep(t_p *p, t_data d)
{
	printf("%d %d is sleeping\n", get_timestamp_ms(), p->number);
	usleep(d.time_to_sleep * 1000);
}

void	*p_thread(void *arg, t_data d)
{
	t_p	*p;

	p = (t_p *)arg;
	while (1)
	{
		think(p);
		eat(p, d);
		if (d.number_of_times_each_p_must_eat > 0)
		{
			p->meals_eaten++;
			if (p->meals_eaten >= d.number_of_times_each_p_must_eat)
				break ;
		}
		do_sleep(p, d);
	}
	return (NULL);
}

int	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	main(int argc, char **argv)
{
	t_data	d;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_ps time_to_die time_to_eat time_to_sleep [number_of_times_each_p_must_eat]\n", argv[0]);
		return (1);
	}
	d.number_of_ps = atoi(argv[1]);
	d.time_to_die = atoi(argv[2]);
	d.time_to_eat = atoi(argv[3]);
	d.time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		d.number_of_times_each_p_must_eat = atoi(argv[5]);
	else
		d.number_of_times_each_p_must_eat = -1;
	d.total_meals_eaten = 0;
	if (d.number_of_ps <= 0 || d.time_to_die < 0
		|| d.time_to_eat < 0 || d.time_to_sleep < 0)
	{
		printf("Error: Invalid arguments.\n");
		return (1);
	}
	d.forks = (pthread_mutex_t **) malloc(d.number_of_ps * sizeof(pthread_mutex_t *));
	i = 0;
	while (i < d.number_of_ps)
	{
		d.forks[i] = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		i++;
	}
	d.ps = (t_p **)malloc(d.number_of_ps * sizeof(t_p *));
	i = 0;
	while (i < d.number_of_ps)
	{
		d.ps[i] = (t_p *)malloc(sizeof(t_p));
		d.ps[i]->number = i + 1;
		d.ps[i]->left_fork = d.forks[i];
		d.ps[i]->right_fork = d.forks[(i + 1) % d.number_of_ps];
		d.ps[i]->meals_eaten = 0;
		gettimeofday(&d.ps[i]->last_meal_time, NULL);
		if (pthread_mutex_init(d.forks[i], NULL) != 0)
		{
			printf("Error: Failed to initialize mutex for fork %d\n", i + 1);
			return (1);
		}
		if (pthread_create(&d.ps[i]->thread, NULL, p_thread, &d.ps[i]) != 0)
		{
			printf("Error: Failed to create thread for p %d\n", i + 1);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < d.number_of_ps)
	{
		pthread_join(d.ps[i]->thread, NULL);
		// pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(d.forks);
	return (0);
}
