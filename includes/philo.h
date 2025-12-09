/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:11:43 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/09 16:44:07 by vmatsuda         ###   ########.fr       */
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
# include <stdint.h>
# include <unistd.h>

typedef struct s_all	t_all;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	bool				is_eating;
	int					meal_eaten;
	int					philos_count;
	uint64_t			die_time;
	uint64_t			eat_time;
	uint64_t			last_meal_time;
	uint64_t			sleep_time;
	int					meal_stock;
	uint64_t			think_time;
	pthread_mutex_t		meal_mtx;
	pthread_mutex_t		*lfork_mtx;
	pthread_mutex_t		*rfork_mtx;
	t_all				*all;
}						t_philo;

typedef struct s_all
{
	int					philos_count;
	bool				dead_flag;
	uint64_t			start_time;
	pthread_mutex_t		meal_mtx;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		write_mtx;
	pthread_t			monitor;
	pthread_t			*ph_thread_pool;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_all;

int						check_is_die(t_philo *philo);
void					write_die_time(t_philo *philo);
uint64_t				get_elapsed_time(uint64_t start_time);
uint64_t				sec_to_millis(uint64_t sec);
uint64_t				micros_to_millis(uint64_t usec);
void					ft_usleep(uint64_t milliseconds);
int						run_threads(t_all *all, int n);
int						main_process(t_all *all, int n);
pthread_mutex_t			*alloc_forks(int n);
int						free_all(t_all *all, int n);
t_philo					*alloc_philos(int n);
int						ft_atoi(const char *str);
int						*parse_nums(int ac, char **av, int *args);
uint64_t				get_millis_time(void);
void	print_philos(t_all *all, int n); // delete
// pthread_mutex_t *init_mtxs(pthread_mutex_t *mtxs, t_all *all);
void					free_philos(t_philo *philos, int n);
pthread_t				*free_threads(pthread_t *threads, int n);
pthread_t				*alloc_threads(int n);
void					*do_monitoring(void *arg);
void					*do_action(void *arg);
int						init_philo(t_philo *philo, t_all *all, int *args);
int						init_all(t_all *all, int *args);
int						ft_isdigit(unsigned long c);
long					ft_atoi_long(const char *str, bool *error);
int						validate_input_data(int ac, char **av);

#endif