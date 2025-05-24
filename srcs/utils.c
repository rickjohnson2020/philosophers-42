/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:40:19 by riyano            #+#    #+#             */
/*   Updated: 2025/05/16 18:55:44 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"
#include <sys/time.h>

void	error_and_exit(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 21);
	}
	return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void	cleanup(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_join(rules->philos[i].thread, NULL) != 0)
			error_and_exit("Failed to join philosopher thread.");
		i++;
	}
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_mutex_destroy(&rules->forks[i]) != 0)
			error_and_exit("Failed to destroy fork.");
		i++;
	}
	if (pthread_mutex_destroy(&rules->print_mutex) != 0)
		error_and_exit("Failed to destroy print mutex.");
	if (pthread_mutex_destroy(&rules->meal_check_mutex) != 0)
		error_and_exit("Failed to destroy meal check mutex.");
	free(rules->philos);
	free(rules->forks);
}
