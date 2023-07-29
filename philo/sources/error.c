/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:38:46 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/29 03:05:37 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	free_ps(void)
{
	int	i;

	i = 0;
	if (get_d()->ps == NULL)
		return ;
	while (i < get_d()->nb_of_ps)
	{
		free(get_d()->ps[i]);
		i++;
	}
	if (get_d()->ps != NULL)
	{
		free(get_d()->ps);
		get_d()->ps = NULL;
	}
}

static void	free_forks(void)
{
	int	i;

	if (get_d()->forks == NULL)
		return ;
	i = 0;
	while (i < get_d()->nb_of_ps)
	{
		if (get_d()->forks[i]->m_fork != NULL)
		{
			pthread_mutex_destroy(get_d()->forks[i]->m_fork);
			free(get_d()->forks[i]->m_fork);
		}
		free(get_d()->forks[i]);
		i++;
	}
	free(get_d()->forks);
}

void	free_all(void)
{
	int	i;

	i = 0;
	while (i < get_d()->nb_of_ps && i < get_d()->nb_of_ps)
		pthread_join(get_d()->ps[i++]->thread, NULL);
	i = 0;
	while (i < get_d()->nb_of_ps)
		pthread_mutex_destroy(get_d()->forks[i++]->m_fork);
	pthread_mutex_destroy(&get_d()->m_dead);
	pthread_mutex_destroy(&get_d()->m_last_meal);
	pthread_mutex_destroy(&get_d()->m_finished);
	pthread_mutex_destroy(&get_d()->m_print);
	free_ps();
	free_forks();
}

void	error(char *reason)
{
	free_all();
	pthread_mutex_lock(&get_d()->m_print);
	write(2, "Error\n", 6);
	write(2, reason, ft_strlen(reason));
	pthread_mutex_unlock(&get_d()->m_print);
	exit(EXIT_FAILURE);
}
