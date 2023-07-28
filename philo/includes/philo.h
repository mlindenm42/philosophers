/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:15:16 by mlindenm          #+#    #+#             */
/*   Updated: 2023/07/28 20:23:09 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h> //NULL; write();
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_fork {
	int				number;
	pthread_mutex_t	*m_fork;
}	t_fork;

typedef struct s_p {
	int				number;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct timeval	last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
}	t_p;

typedef struct s_data {
	t_p				**ps;
	t_fork			**forks;
	int				nb_of_ps;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				have_to_eat;
	long			start_time;
	int				death;
	int				finished;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_finished;
	pthread_mutex_t	m_last_meal;
	pthread_mutex_t	m_print;
}	t_data;

// check.c
void	check_arg(int argc, char *argv[]);
void	check_dead_finished(void);

// error.c
void	error(char *reason);
void	error_data(char *reason);

// init.c
void	init(int argc, char *argv[]);

// philo_functions.c
int		dead(void);
void	think(t_p *p, t_data d);
void	do_sleep(t_p *p, t_data d);
void	eat(t_p *p, t_data d);

// pthread.c
t_data	*get_d(void);
long	get_time(void);
void	*p_thread(void *arg);

// utils.c
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);

#endif
