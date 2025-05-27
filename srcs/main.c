/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:50:06 by riyano            #+#    #+#             */
/*   Updated: 2025/05/04 17:59:46 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_atoi_safe(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (str[i] == '\0')
		error_and_exit("Invalid argument\n");
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			error_and_exit("Invalid argument\n");
		result = result * 10 + (str[i++] - '0');
	}
	return (result * sign);
}

void	parse_args(int ac, char **av, t_rules *rules)
{
	int	i;

	if (ac != 5 && ac != 6)
		error_and_exit("Invalid number of arguments");
	i = 1;
	while (i < ac)
	{
		if (ft_atoi_safe(av[i]) < 0)
			error_and_exit("All arguments must be positive integers\n");
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
}

int	main(int ac, char **av)
{
	t_rules	rules;
	//t_philo	*philos;
	printf("Parsing arguments...\n");
	parse_args(ac, av, &rules);
	printf("Initializing rules...\n");
	init_rules(&rules);
	printf("Initializing philosophers...\n");
	init_philos(&rules);
	printf("Starting threads...\n");
	start_threads(&rules);
	cleanup(&rules);
	printf("Done.\n");
	return (0);
}
