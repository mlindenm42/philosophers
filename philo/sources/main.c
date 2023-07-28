/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:14:50 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/28 20:22:58 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	check_arg(argc, argv);
	init(argc, argv);
	check_dead_finished();
	return (0);
}
