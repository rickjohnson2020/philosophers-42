#include "../includes/philo.h"

static void	think(t_philo *philo);
static void	take_forks(t_philo *philo);
static void	eat(t_philo *philo);
static void	sleeep(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (is_simulation_active(philo->rules))
	{
		if (is_simulation_active(philo->rules))
			think(philo);
		if (philo->id % 2 == 0)
			usleep(100);
		if (is_simulation_active(philo->rules))
			take_forks(philo);
		if (is_simulation_active(philo->rules))
			eat(philo);
		if (is_simulation_active(philo->rules))
			sleeep(philo);
	}
	return (NULL);
}

static void	think(t_philo *philo)
{
	safe_print(philo, "is thinking");
	//usleep(100);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		//usleep(100);
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->meal_check_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->rules->meal_check_mutex);
	safe_print(philo, "is eating");
	usleep(philo->rules->time_to_eat * 1000);
	philo->meals_eaten++;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);

	}
}

static void	sleeep(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	usleep(philo->rules->time_to_sleep * 1000);
}

