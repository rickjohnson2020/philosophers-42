/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:19:50 by riyano            #+#    #+#             */
/*   Updated: 2025/05/04 17:41:02 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//each philosopher need to be a thread
typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal_time; //time passed from the last meal
	size_t			time_to_die; //time passed from the last meal time
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_times_must_eat; //optional argument
	//int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct	s_program
{
	int		num_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		dead_flag;
	t_philo	*philos;
}	t_program;


#endif
