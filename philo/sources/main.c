/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:14:50 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/29 01:59:52 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(long time)
{
	long	now;

	now = get_time();
	while ((get_time() - now) < time)
		usleep(200);
}

int	main(int argc, char **argv)
{
	check_arg(argc, argv);
	init(argc, argv);
	check_dead_finished();
	free_all();
	return (0);
}
