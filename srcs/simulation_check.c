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

int	is_simulation_active(t_rules *rules)
{
	int	active;

	pthread_mutex_lock(&rules->sim_end_mutex);
	active = !rules->simulation_end;
	pthread_mutex_unlock(&rules->sim_end_mutex);
	return (active);
}
