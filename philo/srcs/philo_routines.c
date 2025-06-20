/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:45:47 by riyano            #+#    #+#             */
/*   Updated: 2025/05/28 18:29:29 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static void	think(t_philo *philo);
static int	take_forks(t_philo *philo);
static int	eat(t_philo *philo);
static void	sleeep(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		smart_usleep(1, philo->rules);
	while (is_simulation_active(philo->rules))
	{
		think(philo);
		if (philo->id % 2 == 1)
			smart_usleep(1, philo->rules);
		if (!is_simulation_active(philo->rules))
			break ;
		if (!eat(philo))
			break ;
		if (!is_simulation_active(philo->rules))
			break ;
		sleeep(philo);
	}
	return (NULL);
}

static void	think(t_philo *philo)
{
	safe_print(philo, "is thinking", 0);
}

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork", 0);
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork", 0);
		if (philo->rules->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
			return (0);
		}
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork", 0);
	}
	return (1);
}

static int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	if (is_simulation_active(philo->rules))
	{
		safe_print(philo, "is eating", 0);
		pthread_mutex_lock(&philo->rules->meal_check_mutex);
		philo->last_meal_time = get_time_in_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->rules->meal_check_mutex);
		smart_usleep(philo->rules->time_to_eat, philo->rules);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
	}
	return (1);
}

static void	sleeep(t_philo *philo)
{
	safe_print(philo, "is sleeping", 0);
	smart_usleep(philo->rules->time_to_sleep, philo->rules);
}
