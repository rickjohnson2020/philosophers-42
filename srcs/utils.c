/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:40:19 by riyano            #+#    #+#             */
/*   Updated: 2025/05/28 17:23:50 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

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
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	optimized_usleep(long long t)
{
	long long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < t)
		usleep(1000);
}

void	cleanup(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_join(rules->philos[i++].thread, NULL) != 0)
			error_and_exit("Failed to join philosopher thread.");
	}
	if (pthread_join(rules->monitor, NULL) != 0)
		error_and_exit("Failed to join philosopher thread.");
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_mutex_destroy(&rules->forks[i++]) != 0)
			error_and_exit("Failed to destroy fork.");
	}
	if (pthread_mutex_destroy(&rules->print_mutex) != 0)
		error_and_exit("Failed to destroy print mutex.");
	if (pthread_mutex_destroy(&rules->meal_check_mutex) != 0)
		error_and_exit("Failed to destroy meal check mutex.");
	if (pthread_mutex_destroy(&rules->sim_end_mutex) != 0)
		error_and_exit("Failed to destroy sim end mutex.");
	free(rules->philos);
	free(rules->forks);
}
