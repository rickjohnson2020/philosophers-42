/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:19:50 by riyano            #+#    #+#             */
/*   Updated: 2025/05/28 18:34:20 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long long		last_meal_time;
	t_rules			*rules;
}	t_philo;

typedef struct s_rules
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				simulation_end;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_check_mutex;
	pthread_mutex_t	sim_end_mutex;
	t_philo			*philos;
	pthread_t		monitor;
}	t_rules;

void		error_and_exit(const char *msg);
long long	get_time_in_ms(void);
void		smart_usleep(long long t, t_rules *rules);
void		init_rules(t_rules *rules);
void		init_philos(t_rules *rules);
void		safe_print(t_philo *philo, char *msg, int dying_msg);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
int			is_simulation_active(t_rules *rules);

#endif
