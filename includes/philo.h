/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:11:43 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/11 18:49:55 by vmatsuda         ###   ########.fr       */
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

typedef enum ph_state
{
	CREATED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	FINISHED = 4
}						t_ph_state;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	t_ph_state			state;
	int					meal_eaten;
	int					philos_count;
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
	int					philos_count;
	bool				dead_flag;
	bool				goal_flag;
	uint64_t			time_created;
	int					meal_stock;
	pthread_mutex_t		goal_mtx;
	pthread_mutex_t		meal_mtx;
	pthread_mutex_t		state_mtx;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		write_mtx;
	pthread_t			monitor;
	pthread_t			*ph_thread_pool;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_all;

void change_state_and_time_last_meal(t_philo *philo);
int increment_eaten_meal_and_check_finish(t_philo *philo);
// int						check_end_flags(t_philo *philo);
int						check_goal(t_all *all);
int						check_is_finish(t_philo *philo);
void					print_message(t_philo *philo, char *str);
int						check_can_eat(t_philo *philo);
void					do_sleep(t_philo *philo);
void					do_think(t_philo *philo);
int						do_eat(t_philo *philo);
int						one_philo_case(t_philo *philo);
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