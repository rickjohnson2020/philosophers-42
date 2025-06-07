/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:53:40 by riyano            #+#    #+#             */
/*   Updated: 2025/05/28 18:32:05 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static int	all_ate_enough(t_rules *rules);
static int	is_philo_dead(t_philo *philo);

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (is_simulation_active(rules))
	{
		i = 0;
		while (i < rules->num_philos)
		{
			if (is_philo_dead(&rules->philos[i]) || all_ate_enough(rules))
			{
				pthread_mutex_lock(&rules->sim_end_mutex);
				rules->simulation_end = 1;
				pthread_mutex_unlock(&rules->sim_end_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

static int	is_philo_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->rules->meal_check_mutex);
	is_dead = (get_time_in_ms() - philo->last_meal_time
		> (long long)philo->rules->time_to_die);
	pthread_mutex_unlock(&philo->rules->meal_check_mutex);
	if (is_dead)
	{
		safe_print(philo, "died", 1);
		return (1);
	}
	return (0);
}

static int	all_ate_enough(t_rules *rules)
{
	int	i;

	if (rules->meals_required == -1)
		return (0);
	i = 0;
	while (i < rules->num_philos)
	{
		pthread_mutex_lock(&rules->meal_check_mutex);
		if (rules->philos[i].meals_eaten < rules->meals_required)
		{
			pthread_mutex_unlock(&rules->meal_check_mutex);
			return (0);
		}
		pthread_mutex_unlock(&rules->meal_check_mutex);
		i++;
	}
	return (1);
}
