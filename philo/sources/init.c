/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:18:30 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/29 19:45:32 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_forks(void)
{
	int	i;

	i = 0;
	get_d()->forks = NULL;
	get_d()->forks = (t_fork **) malloc(get_d()->nb_of_ps * sizeof(t_fork *));
	if (get_d()->forks == NULL)
		error("malloc forks failed");
	while (i < get_d()->nb_of_ps)
	{
		get_d()->forks[i] = NULL;
		get_d()->forks[i] = (t_fork *) malloc(sizeof(t_fork));
		if (get_d()->forks[i] == NULL)
			error("malloc fork failed");
		get_d()->forks[i]->number = i;
		get_d()->forks[i]->m_fork = NULL;
		get_d()->forks[i]->m_fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t));
		if (get_d()->forks[i] == NULL)
			error("malloc m_fork failed");
		if (pthread_mutex_init(get_d()->forks[i]->m_fork, NULL) != 0)
			error("Failed to initialize mutex for fork %d\n");
		i++;
	}
}

static void	init_ps(void)
{
	int	i;

	i = 0;
	get_d()->ps = NULL;
	get_d()->ps = (t_p **)malloc(get_d()->nb_of_ps * sizeof(t_p *));
	if (get_d()->ps == NULL)
		error("malloc ps failed");
	while (i < get_d()->nb_of_ps)
	{
		get_d()->ps[i] = NULL;
		get_d()->ps[i] = (t_p *)malloc(sizeof(t_p));
		if (get_d()->ps[i] == NULL)
			error("malloc p failed");
		get_d()->ps[i]->number = i + 1;
		get_d()->ps[i]->left_fork = get_d()->forks[i];
		get_d()->ps[i]->right_fork = get_d()->forks[(i + 1)
		% get_d()->nb_of_ps];
		get_d()->ps[i]->last_meal_time = 0;
		get_d()->ps[i]->meals_eaten = 0;
		if (pthread_create(&get_d()->ps[i]->thread, NULL,
				&p_thread, get_d()->ps[i]) != 0)
			error("Failed to create thread for p %d\n");
		i++;
	}
}

void	init(int argc, char *argv[])
{
	get_d()->start_time = get_time();
	get_d()->nb_of_ps = ft_atoi(argv[1]);
	get_d()->time_to_die = ft_atoi(argv[2]);
	get_d()->time_to_eat = ft_atoi(argv[3]);
	get_d()->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		get_d()->have_to_eat = ft_atoi(argv[5]);
	else
		get_d()->have_to_eat = -1;
	get_d()->death = 0;
	get_d()->finished = 0;
	if (pthread_mutex_init(&(get_d()->m_dead), NULL) != 0)
		error("Failed to initialize mutex for eat %d\n");
	if (pthread_mutex_init(&(get_d()->m_last_meal), NULL) != 0)
		error("Failed to initialize mutex for last_meal %d\n");
	if (pthread_mutex_init(&(get_d()->m_finished), NULL) != 0)
		error("Failed to initialize mutex for finished %d\n");
	if (pthread_mutex_init(&(get_d()->m_print), NULL) != 0)
		error("Failed to initialize mutex for print %d\n");
	init_forks();
	init_ps();
}
