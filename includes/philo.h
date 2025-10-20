/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:11:43 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/20 22:45:33 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "limits.h"
# include "pthread.h"
# include "stdbool.h"
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "sys/time.h"
# include <unistd.h>

typedef struct s_all	t_all;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					meal_eaten;
	int					philos_count;
	size_t				die_time;
	size_t				eat_time;
	size_t				last_meal_time;
	size_t				sleep_time;
	int					meal_stock;
	size_t				think_time;
	size_t				start_time;
	pthread_mutex_t		*lfork_mtx;
	pthread_mutex_t		*rfork_mtx;
	pthread_mutex_t		*meal_mtx;
	pthread_mutex_t		*dead_mtx;
	pthread_mutex_t		*write_mtx;
	t_all				*all;
}						t_philo;

typedef struct s_all
{
	int					philos_count;
	int					dead_flag;
	pthread_mutex_t		meal_mtx;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		write_mtx;
	pthread_t			*thread_pool;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_all;

size_t					get_elapsed_time(size_t start_time);
void					usleep_sec(int sec);
size_t					sec_to_millis(int sec);
size_t					micros_to_millis(int usec);
void					usleep_sec(int sec);
int						init_thread_pool(t_all *all, int n);
int						main_process(t_all *all, int n);
pthread_mutex_t			*alloc_forks(int n);
int						free_all(t_all *all, int n);
t_philo					*alloc_philos(int n);
int						ft_atoi(const char *str);
int						*parse_nums(int ac, char **av, int *args);
size_t					get_millis_time(void);
void	print_philos(t_all *all, int n); // delete
// pthread_mutex_t *init_mtxs(pthread_mutex_t *mtxs, t_all *all);
void					free_philos(t_philo *philos, int n);
pthread_t				*free_threads(pthread_t *threads, int n);
pthread_t				*alloc_thread_pool(int n);
void					*do_monitoring(void *arg);
void					*do_action(void *arg);
int						init_philo(t_philo *philo, t_all *all, int *args);
int						init_all(t_all *all, int *args);
int						ft_isdigit(unsigned long c);
long					ft_atoi_long(const char *str, bool *error);
int						validate_input_data(int ac, char **av);

#endif