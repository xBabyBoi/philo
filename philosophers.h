/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:14:42 by yel-qori          #+#    #+#             */
/*   Updated: 2025/07/05 16:55:48 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>


# define MAX_PHILOSOPHERS 200
# define MAX_FORKS 200

typedef struct s_args
{
    int n_philos;
    int t_sleep;
    int t_eat;
    int t_die;
    int meal_count;
    int flag_meal_count;
    int death_flag;
}   t_args; 

typedef struct s_philos
{
    int id;
    int meals_counter;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_args *args;
}t_philos;


int	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(char *str);
int	ft_atoi(char *str);
int	ft_isdigit(int a);
void *safe_malloc(size_t bytes);
long get_time_ms(void);



int check_correct_args(char **av);
int check_valid_args(char *av);
void routine(t_philos *philo);
int init_philos(t_philos *philos, t_args *args, pthread_mutex_t *forks);
t_args *convert_args(char **av);
int create_threads(pthread_t *threads, t_philos *philos, t_args *args);
int init_mutex(pthread_mutex_t *forks, int n_philos);
void thinking(t_philos *philo);
void sleeping(t_philos *philo);
void routine(t_philos *philo);




#endif