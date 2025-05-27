#include "../includes/philo.h"

static void	think(t_philo *philo);
static void	take_forks(t_philo *philo);
static void	eat(t_philo *philo);
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
	safe_print(philo, "is thinking", 0);
	//usleep(100);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		//usleep(100);
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a right fork", 0);
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a left fork", 0);
	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has taken a left fork", 0);
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has taken a right fork", 0);
	}
}

static void	eat(t_philo *philo)
{
	safe_print(philo, "is eating", 0);
	pthread_mutex_lock(&philo->rules->death_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->death_mutex);
	usleep(philo->rules->time_to_eat * 1000);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has put down a right fork", 0);
		pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has put down a left fork", 0);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
		safe_print(philo, "has put down a left fork", 0);
		pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
		safe_print(philo, "has put down a right fork", 0);

	}
}

static void	sleeep(t_philo *philo)
{
	safe_print(philo, "is sleeping", 0);
	usleep(philo->rules->time_to_sleep * 1000);
}

