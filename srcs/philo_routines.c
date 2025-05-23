#include "../includes/philo.h"

static void	think(t_philo *philo);
static void	take_forks(t_philo *philo);
static void	eat(t_philo *philo);
static void	sleeep(t_philo *philo);

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
	while (is_simulation_active(philo->rules))
	{
		think(philo);
		take_forks(philo);
		eat(philo);
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
	pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
}

static void	sleeep(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	usleep(philo->rules->time_to_sleep * 1000);
}

