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
#include <sys/time.h>

void	error_and_exit(const char *msg)
{
	printf(msg);
	exit(EXIT_FAILURE);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 21);
	}
	return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
