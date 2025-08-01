/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:14:42 by yel-qori          #+#    #+#             */
/*   Updated: 2025/08/01 10:34:48 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOSOPHERS 200
# define MAX_FORKS 200

typedef struct s_args	t_args;
typedef struct s_philos	t_philos;

typedef struct s_philos
{
	int					id;
	int					meals_counter;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_args				*args;
	long				last_meal_time;
	pthread_mutex_t		meal_mutex;
}						t_philos;

typedef struct s_args
{
	int					n_philos;
	int					t_sleep;
	int					t_eat;
	int					t_die;
	int					meal_count;
	int					flag_meal_count;
	int					death_flag;
	long				start_time;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		print_mutex;
	t_philos			*philos;
}						t_args;

typedef struct s_init_data
{
	t_args				*data;
	pthread_mutex_t		*forks;
	t_philos			*philosophers;
	pthread_t			*threads;
}						t_init_data;

int						ft_putstr_fd(char *s, int fd);
size_t					ft_strlen(char *str);
int						ft_atoi(char *str);
int						ft_isdigit(int a);
void					*safe_malloc(size_t bytes);
long					get_time_ms(void);
int						ft_usleep(long ms);

int						is_dead(t_philos *philo);
int						all_meals_completed(t_philos *philos, int n_philos);
void					destory_all(char *str, t_philos *philos,
							pthread_mutex_t *forks);
int						is_dead_global(t_args *args);
void					safe_print(t_philos *philo, char *action);
int						check_correct_args(char **av);
int						check_valid_args(char *av);
void					set_death_flag(t_args *args);
void					routine(t_philos *philo);
int						init_philos(t_philos *philos, t_args *args,
							pthread_mutex_t *forks);
t_args					*convert_args(char **av);
int						create_threads(pthread_t *threads, t_philos *philos,
							t_args *args, pthread_mutex_t *forks);
int						init_mutex(pthread_mutex_t *forks, int n_philos);
void					thinking(t_philos *philo);
void					sleeping(t_philos *philo);
void					routine(t_philos *philo);
void					eating(t_philos *philo);
int						check_philosopher_death(t_philos *philos, int i);
void					monitoring(t_philos *philos);

#endif