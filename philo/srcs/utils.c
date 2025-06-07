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

void	smart_usleep(long long ms, t_rules *rules)
{
	long long	start;

	start = get_time_in_ms();
	while (is_simulation_active(rules) && (get_time_in_ms() - start < ms))
		usleep(500);
}

void	safe_print(t_philo *philo, char *msg, int dying_msg)
{
	if (dying_msg)
	{
		pthread_mutex_lock(&philo->rules->print_mutex);
		printf("%lld %d %s\n", get_time_in_ms() - philo->rules->start_time,
			philo->id, msg);
		pthread_mutex_unlock(&philo->rules->print_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->rules->print_mutex);
		if (is_simulation_active(philo->rules))
		{
			printf("%lld %d %s\n", get_time_in_ms() - philo->rules->start_time,
				philo->id, msg);
		}
		pthread_mutex_unlock(&philo->rules->print_mutex);
	}
}
