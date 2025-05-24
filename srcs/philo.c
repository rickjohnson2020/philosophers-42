#include "../includes/philo.h"

void	safe_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%lld %d %s\n", get_time_in_ms() - philo->rules->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

int	is_simulation_active(t_rules *rules)
{
	int	active;

	pthread_mutex_lock(&rules->sim_end_mutex);
	active = !rules->sim_end;
	pthread_mutex_unlock(&rules->sim_end_mutex);
	return (active);
}

void	start_threads(t_rules *rules)
{
	int			i;
	pthread_t	monitor;

	rules->start_time = get_time_in_ms();
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_create(&rules->philos[i].thread, NULL,
				&philo_routine, &rules->philos[i]) != 0)
			error_and_exit("Failed to create philosopher thread.\n");
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, rules) != 0)
		error_and_exit("Failed to create monitor thread.\n");
	pthread_detach(monitor);
}

