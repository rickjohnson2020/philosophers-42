/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:41:41 by riyano            #+#    #+#             */
/*   Updated: 2025/05/28 18:29:56 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	safe_print(t_philo *philo, char *msg, int dying_msg)
{
	if (dying_msg)
	{
		pthread_mutex_lock(&philo->rules->print_mutex);
		printf("%lld %d %s\n", get_time_in_ms() - philo->rules->start_time,
			philo->id, msg);
		pthread_mutex_unlock(&philo->rules->print_mutex);
	}
	else if (is_simulation_active(philo->rules))
	{
		pthread_mutex_lock(&philo->rules->print_mutex);
		printf("%lld %d %s\n", get_time_in_ms() - philo->rules->start_time,
			philo->id, msg);
		pthread_mutex_unlock(&philo->rules->print_mutex);
	}
}

int	is_simulation_active(t_rules *rules)
{
	int	active;

	pthread_mutex_lock(&rules->sim_end_mutex);
	active = !rules->simulation_end;
	pthread_mutex_unlock(&rules->sim_end_mutex);
	return (active);
}

void	start_threads(t_rules *rules)
{
	int	i;

	rules->start_time = get_time_in_ms();
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_create(&rules->philos[i].thread, NULL,
				&philo_routine, &rules->philos[i]) != 0)
			error_and_exit("Failed to create philosopher thread.");
		i++;
	}
	if (pthread_create(&rules->monitor, NULL, &monitor_routine, rules) != 0)
		error_and_exit("Failed to create monitor thread.");
}
