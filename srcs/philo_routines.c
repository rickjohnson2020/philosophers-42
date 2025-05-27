#include "../includes/philo.h"

static void	think(t_philo *philo);
static int	take_forks(t_philo *philo);
static int	eat(t_philo *philo);
static void	sleeep(t_philo *philo);

static void	optimized_usleep(unsigned long t)
{
	unsigned long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < t)
		usleep(1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		optimized_usleep(1);
	while (is_simulation_active(philo->rules))
	{
		if (is_simulation_active(philo->rules))
			think(philo);
		if (philo->id % 2 == 1)
			optimized_usleep(1);
		if (is_simulation_active(philo->rules))
		{
			if (!eat(philo))
				return (NULL);
		}
		if (is_simulation_active(philo->rules))
			sleeep(philo);
	}
	return (NULL);
}

static void	think(t_philo *philo)
{
	safe_print(philo, "is thinking", 0);
	//usleep(100);
}

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		//usleep(100);
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork", 0);
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a fork", 0);
		if (philo->rules->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
			return (0);
		}
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a fork", 0);
	}
	return (1);
}

static int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	if (is_simulation_active(philo->rules))
	{
		safe_print(philo, "is eating", 0);
		pthread_mutex_lock(&philo->rules->death_mutex);
		philo->last_meal_time = get_time_in_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->rules->death_mutex);
		usleep(philo->rules->time_to_eat * 1000);
	}
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
	return (1);
}

static void	sleeep(t_philo *philo)
{
	safe_print(philo, "is sleeping", 0);
	usleep(philo->rules->time_to_sleep * 1000);
}

