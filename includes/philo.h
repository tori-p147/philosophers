/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:11:43 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/21 19:00:59 by vmatsuda         ###   ########.fr       */
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

typedef enum ph_action
{
	FORK = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3
}						t_ph_action;

typedef struct s_philo
{
	size_t				id;
	bool				is_eating;
	pthread_t			thread;
	uint64_t			time_created;
	size_t				meal_eaten;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_last_meal;
	uint64_t			time_to_sleep;
	pthread_mutex_t		*lfork_mtx;
	pthread_mutex_t		*rfork_mtx;
	t_all				*all;
}						t_philo;

typedef struct s_all
{
	bool				dead_flag;
	size_t				philos_count;
	size_t				meal_stock;
	size_t				ph_finished;
	pthread_mutex_t		meal_mtx;
	pthread_mutex_t		time_mtx;
	pthread_mutex_t		print_mtx;
	pthread_t			monitor;
	pthread_t			*ph_thread_pool;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_all;

void					check_all_ph_started(t_philo *philo);
void					print_die_time(t_philo *philo, uint64_t now);
void					set_time_last_meal(t_philo *philo);
int						free_exit(t_all *all, int *args, int exit_status);
int						increment_eaten_meal(t_philo *philo);
int						check_eaten_meal(t_philo *philo);
void					print_message(t_philo *ph, uint64_t now, t_ph_action a);
int						check_can_eat(t_philo *philo);
void					do_sleep(t_philo *philo);
void					do_think(t_philo *philo);
void					do_eat(t_philo *philo);
int						check_die(t_philo *philo);
int						exit_dead_flag(t_philo *philo);
uint64_t				get_elapsed_time(uint64_t start_time);
uint64_t				sec_to_millis(uint64_t sec);
uint64_t				micros_to_millis(uint64_t usec);
void					ft_usleep(uint64_t milliseconds, t_philo *philo);
int						run_threads(t_all *all, int n);
pthread_mutex_t			*alloc_forks(int n);
int						free_all(t_all *all, int n);
t_philo					*alloc_philos(int n);
int						ft_atoi(const char *str);
int						*parse_nums(int ac, char **av, int *args);
uint64_t				get_millis_time(void);
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