/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:21:26 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/28 04:26:21 by mlindenm         ###   ########.fr       */
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
