#include "../includes/philo.h"

static int	is_philo_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->death_mutex);
	if (rules->is_dead)
	{
		pthread_mutex_unlock(&rules->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&rules->death_mutex);
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
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->philos[i].meals_eaten < rules->meals_required)
		{
			pthread_mutex_unlock(&rules->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&rules->death_mutex);
		i++;
	}
	return (1);
}

int	is_simulation_active(t_rules *rules)
{
	if (is_philo_dead(rules) || all_ate_enough(rules))
		return (0);
	return (1);
}