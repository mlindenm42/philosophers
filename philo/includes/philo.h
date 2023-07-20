/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:15:16 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/20 21:55:15 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h> //NULL; write();
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_p {
	int				number;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
}	t_p;

typedef struct s_data {
	t_p				**ps;
	pthread_mutex_t	**forks;
	int				number_of_ps;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_p_must_eat;
	int				total_meals_eaten;
}	t_data;

int		get_timestamp_ms(void);

// error.c
void	error(char *reason);

#endif
