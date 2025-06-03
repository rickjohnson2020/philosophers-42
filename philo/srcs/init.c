/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:17:32 by riyano            #+#    #+#             */
/*   Updated: 2025/05/28 18:16:08 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	init_rules(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_philos);
	if (!rules->forks)
		error_and_exit("Failed to allocate forks.");
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			error_and_exit("Failed to initialize a fork mutex.");
		i++;
	}
	rules->simulation_end = 0;
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		error_and_exit("Failed to initialize print mutex.");
	if (pthread_mutex_init(&rules->meal_check_mutex, NULL) != 0)
		error_and_exit("Failed to initialize meal check mutex.");
	if (pthread_mutex_init(&rules->sim_end_mutex, NULL) != 0)
		error_and_exit("Failed to initialize simulation end mutex.");
}

void	init_philos(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * rules->num_philos);
	if (!philos)
		error_and_exit("Failed to allocate philos.");
	i = 0;
	while (i < rules->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % rules->num_philos;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = get_time_in_ms();
		philos[i].rules = rules;
		i++;
	}
	rules->philos = philos;
}
