/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:50:06 by riyano            #+#    #+#             */
/*   Updated: 2025/05/28 17:20:25 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_atoi_safe(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (str[i] == '\0')
		error_and_exit("Invalid argument");
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			error_and_exit("Invalid argument");
		result = result * 10 + (str[i++] - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && -(result) < INT_MIN))
			error_and_exit("All arguments must be within the range of Integer");
	}
	return ((int)result * sign);
}

static void	parse_args(int ac, char **av, t_rules *rules)
{
	int	i;

	if (ac != 5 && ac != 6)
		error_and_exit("Invalid number of arguments");
	i = 1;
	while (i < ac)
	{
		if (ft_atoi_safe(av[i]) < 0)
			error_and_exit("All arguments must be positive integers");
		i++;
	}
	rules->num_philos = ft_atoi_safe(av[1]);
	rules->time_to_die = ft_atoi_safe(av[2]);
	rules->time_to_eat = ft_atoi_safe(av[3]);
	rules->time_to_sleep = ft_atoi_safe(av[4]);
	if (ac == 6)
		rules->meals_required = ft_atoi_safe(av[5]);
	else
		rules->meals_required = -1;
	if (rules->num_philos < 1)
		error_and_exit("number of philosophers must be at least 1");
	if (ac == 6 && rules->meals_required == 0)
		error_and_exit("No need to eat — exiting immediately.");
}

static void	start_threads(t_rules *rules)
{
	int	i;

	rules->start_time = get_time_in_ms();
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_create(&rules->philos[i].thread, NULL,
				&philo_routine, &rules->philos[i]) != 0)
			error_and_exit("Failed to create philosopher thread.");
		i++;
	}
	if (pthread_create(&rules->monitor, NULL, &monitor_routine, rules) != 0)
		error_and_exit("Failed to create monitor thread.");
}

static void	cleanup(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_join(rules->philos[i++].thread, NULL) != 0)
			error_and_exit("Failed to join philosopher thread.");
	}
	if (pthread_join(rules->monitor, NULL) != 0)
		error_and_exit("Failed to join philosopher thread.");
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_mutex_destroy(&rules->forks[i++]) != 0)
			error_and_exit("Failed to destroy fork.");
	}
	if (pthread_mutex_destroy(&rules->print_mutex) != 0)
		error_and_exit("Failed to destroy print mutex.");
	if (pthread_mutex_destroy(&rules->meal_check_mutex) != 0)
		error_and_exit("Failed to destroy meal check mutex.");
	if (pthread_mutex_destroy(&rules->sim_end_mutex) != 0)
		error_and_exit("Failed to destroy sim end mutex.");
	free(rules->philos);
	free(rules->forks);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	parse_args(ac, av, &rules);
	init_rules(&rules);
	init_philos(&rules);
	start_threads(&rules);
	cleanup(&rules);
	return (0);
}
