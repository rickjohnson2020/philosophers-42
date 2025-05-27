#include "../includes/philo.h"

void	init_rules(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_philos);
	if (!rules->forks)
		error_and_exit("Failed to allocate forks.");
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			error_and_exit("Failed to initialize a fork mutex.\n");
		i++;
	}
	rules->is_dead = 0;
	//rules->start_time = get_time_in_ms();
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		error_and_exit("Failed to initialize a print mutex.\n");
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		error_and_exit("Failed to initialize a meal check mutex.\n");
}

void	init_philos(t_rules *rules)
{
	t_philo	*philos;
	//t_philo	philos[rules->num_philos];
	int		i;

	philos = malloc(sizeof(t_philo) * rules->num_philos);
	if (!philos)
		error_and_exit("Failed to allocate philos.\n");
	i = 0;
	while (i < rules->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % rules->num_philos;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = get_time_in_ms();
		philos[i].rules = rules;
		i++;
	}
	rules->philos = philos;
}
