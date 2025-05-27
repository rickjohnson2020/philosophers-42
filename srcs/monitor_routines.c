#include "../includes/philo.h"

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
			pthread_mutex_lock(&rules->death_mutex);
			if (get_time_in_ms() - rules->philos[i].last_meal_time > (long long)rules->time_to_die)
			{
				safe_print(&rules->philos[i], "died", 1);
				rules->is_dead = 1;
				pthread_mutex_unlock(&rules->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&rules->death_mutex);
			i++;
		}
		// usleep(100);
	}
	return (NULL);
}

