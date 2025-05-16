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

void	error_and_exit(const char *msg)
{
	printf(msg);
	exit(EXIT_FAILURE);
}

long	ft_atol(const char *str)
{
	long		result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit((unsigned char)*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

void	parse_input(t_program *program, char **av)
{
	program->num_of_philos = ft_atol(av[1]);
	program->time_to_die = ft_atol(av[2]) * 1000;
	program->time_to_eat = ft_atol(av[3]) * 1000;
	program->time_to_sleep = ft_atol(av[4]) * 1000;
	if (program->time_to_die <= 0 || program->time_to_eat <= 0 || program->time_to_sleep <= 0)
		error_and_exit("should be greater than 0\n");

	do_something_with_philos(program->philos);

}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;

}

void	init_philos(t_philo *philos, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		philos[i].id = 1 + i;
		philos[i].meals_eaten = 0;
		philos[i].start_time = get_current_time();
		philos[i].last_meal_time = get_current_time();
		philos[i]->r_fork = pthread_mutex_init(philos[i].r_fork, NULL);
		philos[i]->l_fork = pthered_mutex_init(philos[i].l_fork, NULL);

	}
}

int	main(int ac, char **av)
{
	t_program	program;
	t_philo		*philos;
	if (ac < 5 || ac > 6)
	{
		error_and_exit("Wrong input.\n");
	}
	parse_input(&program, char **av);
	init_program(&program, philos);
	init_philos(philos, program);
}
