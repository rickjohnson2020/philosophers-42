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

void	parse_input(t_table *table, char **av)
{
	table->num_of_philos = ft_atoi(av[1]);
}

int	main(int ac, char **av)
{
	t_table	table;
	if (ac < 5 || ac > 6)
	{
		error_and_exit("Wrong input.\n");
	}
	parse_input(&table, char **av);
}
