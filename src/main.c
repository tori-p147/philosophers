/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:23 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/11 21:53:00 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*prepare_proccess(int ac, char **av, int *args)
{
	if (!validate_input_data(ac, av))
		return (NULL);
	args = parse_nums(ac, av, args);
	if (!args)
		return (NULL);
	return (args);
}

int	run_threads(t_all *all, int n)
{
	int			i;
	uint64_t	time_created;

	i = 0;
	time_created = get_millis_time();
	all->time_created = time_created;
	if (all->philos_count == 1)
		return (one_philo_case(&all->philos[i]));
	while (i < n)
	{
		all->philos[i].time_last_meal = all->time_created;
		pthread_create(&all->philos[i].thread, NULL, do_action,
			&all->philos[i]);
		i++;
	}
	pthread_create(&all->monitor, NULL, do_monitoring, all);
	i = 0;
	while (i < n)
	{
		pthread_join(all->philos[i].thread, NULL);
		i++;
	}
	pthread_join(all->monitor, NULL);
	return (1);
}

int	main_process(t_all *all, int n)
{
	if (!run_threads(all, n))
		return (1);
	return (0);
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
		if (!main_process(&all, args[0]))
			return (free_exit(&all, args, 1));
		return (free_exit(&all, args, 0));
	}
	return (1);
}
