/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:38:46 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/28 05:43:54 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error(char *reason)
{
	pthread_mutex_lock(&get_d()->m_print);
	write(2, "Error\n", 6);
	write(2, reason, ft_strlen(reason));
	pthread_mutex_unlock(&get_d()->m_print);
	exit(EXIT_FAILURE);
}

void	error_data(char *reason)
{
	// free_all(p);
	write(2, "Error\n", 6);
	write(2, reason, ft_strlen(reason));
	exit(EXIT_FAILURE);
}

// void	free_all()
// {
// 	free_ptrptr(p);
// 	while (p->a->start != NULL)
// 		free(remove_node_from_stack_top(p->a));
// 	while (p->b->start != NULL)
// 		free(remove_node_from_stack_top(p->b));
// 	if (p->buffer != NULL)
// 	{
// 		free(p->buffer);
// 		p->buffer = NULL;
// 	}
// 	if (p->a != NULL)
// 	{
// 		free(p->a);
// 		p->a = NULL;
// 	}
// 	if (p->b != NULL)
// 	{
// 		free(p->b);
// 		p->b = NULL;
// 	}
// 	if (p != NULL)
// 	{
// 		free(p);
// 		p = NULL;
// 	}
// }
