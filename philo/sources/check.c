/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:21:26 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/28 19:53:05 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_arg(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		error("Usage: ./philo number_of_ps t_die t_eat t_sleep [meals]\n");
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '0')
			error("Invalid characters!");
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j++]) == 0)
				error("Invalid characters!");
		}
		i++;
	}
}

void	check_dead_finished(void)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < get_d()->nb_of_ps)
		{
			if (get_d()->finished == get_d()->nb_of_ps && get_d()->have_to_eat != -1)
				return ;
			if (((long)get_d()->ps[i]->last_meal_time.tv_sec * 1000)
				+ ((long)get_d()->ps[i]->last_meal_time.tv_usec / 1000)
				+ get_d()->time_to_die < (long)get_time())
			{
				pthread_mutex_lock(&get_d()->m_dead);
				get_d()->death = 1;
				pthread_mutex_unlock(&get_d()->m_dead);
				pthread_mutex_lock(&get_d()->m_print);
				printf("%ld ms %d died\n", get_time() - get_d()->start_time,
					get_d()->ps[i]->number);
				pthread_mutex_unlock(&get_d()->m_print);
				return ;
			}
			i++;
		}
	}
}
