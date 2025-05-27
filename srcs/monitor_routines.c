#include "../includes/philo.h"

static int	all_ate_enough(t_rules *rules);
static int	is_philo_dead(t_philo *philo);
static void	set_simulation_end(t_rules *rules);

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
				set_simulation_end(rules);
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

static void	set_simulation_end(t_rules *rules)
{
	pthread_mutex_lock(&rules->sim_end_mutex);
	rules->sim_end = 1;
	pthread_mutex_unlock(&rules->sim_end_mutex);
}

static int	is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->meal_check_mutex);
	if (get_time_in_ms() - philo->last_meal_time > philo->rules->time_to_die)
	{
		safe_print(philo, "died");
		philo->rules->philo_dead = 1;
		pthread_mutex_unlock(&philo->rules->meal_check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->meal_check_mutex);
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
		if (rules->philos[i].meals_eaten < rules->meals_required)
			return (0);
		i++;
	}
	return (1);
}

