#include "../includes/philo.h"

void	safe_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%lld %d %s\n", get_time_in_ms() - philo->rules->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	think(t_philo *philo)
{
	safe_print(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->meal_check_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->rules->meal_check_mutex);
	safe_print(philo, "is eating");
	usleep(1000);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
}

void	sleep(t_philo *philo)
{
	safe_print(philo, "is sleeping");
}

void	*philo_routine(void *arg)
{
	// 1. think
	// 2. take forks: lock
	// 3. eating: usleep
	//		- mesure last_meal_time
	// 4. put forks
	// 5. sleeping
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (simulation_is_active())
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	while (simulation_is_active())
	{
		i = 0;
		while (i < rules->num_philos)
		{
			pthread_mutex_lock(&rules->meal_check_mutex);
			if (get_time_in_ms - rules->philo[i].last_meal_time > rules->time_to_die)
			{
				safe_print(rules->philo[i], "died");
				rules->all_alive = 0;
				//TODO:
				end_simulation();
			}
			pthread_mutex_unlock(&rules->meal_check_mutex);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	start_threads(t_rules *rules)
{
	int			i;
	pthread_t	*monitor;

	rules->start_time = get_time_in_ms();
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_create(&rules->philos[i]->thread, NULL,
				&philo_routine, rules->philos[i]) != 0)
			error_and_exit("Failed to create philosopher thread.\n");
		i++;
	}
	if (pthread_create(monitor, NULL, &monitor_routine, rules) != 0)
		error_and_exit("Failed to create monitor thread.\n");
}

