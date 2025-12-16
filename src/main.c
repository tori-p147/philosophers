/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:23 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/16 16:10:26 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	one_philo_case(t_philo *philo)
// {
// 	print_message(philo, get_elapsed_time(philo->time_created), FORK);
// 	ft_usleep(philo->time_to_die, philo);
// 	print_die_time(philo, get_elapsed_time(philo->time_created));
// 	return (1);
// }

int	run_threads(t_all *all, int n)
{
	int			i;
	// uint64_t	time_created;

	i = -1;
	// time_created = get_millis_time();
	// if (all->philos_count == 1)
	// 	return (one_philo_case(&all->philos[i]));
	while (++i < n)
	{
		pthread_create(&all->philos[i].thread, NULL, do_action,
			&all->philos[i]);
	}
	pthread_create(&all->monitor, NULL, do_monitoring, all);
	i = -1;
	while (++i < n)
		pthread_join(all->philos[i].thread, NULL);
	pthread_join(all->monitor, NULL);
	return (1);
}

int	*prepare_proccess(int ac, char **av, int *args)
{
	if (!validate_input_data(ac, av))
		return (NULL);
	args = parse_nums(ac, av, args);
	if (!args)
		return (NULL);
	return (args);
}

int	main(int ac, char **av)
{
	t_all	all;
	int		*args;

	args = NULL;
	if (ac == 5 || ac == 6)
	{
		args = prepare_proccess(ac, av, args);
		if (!args)
			return (1);
		if (!init_all(&all, args))
			return (free_exit(&all, args, 1));
		if (!run_threads(&all, args[0]))
			return (free_exit(&all, args, 1));
		return (free_exit(&all, args, 0));
	}
	return (1);
}
