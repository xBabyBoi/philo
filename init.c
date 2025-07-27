/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:02:54 by yel-qori          #+#    #+#             */
/*   Updated: 2025/07/27 15:37:46 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_philos(t_philos *philos, t_args *args, pthread_mutex_t *forks)
{
    int i;
    
    i = 0;
    args->start_time = get_time_ms();
    while (i < args->n_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_counter = 0;
        philos[i].args = args;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % args->n_philos];
        philos[i].last_meal_time = get_time_ms();
        pthread_mutex_init(&philos[i].meal_mutex, NULL);
        i++; 
    }
    return (0);
}

t_args *convert_args(char **av)
{
    t_args *data;
    
    data = malloc(sizeof(t_args));
    if (!data)
        return (NULL);
    data->n_philos = ft_atoi(av[1]);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if (av[5] != NULL)
    {
        data->meal_count = ft_atoi(av[5]);
        data->flag_meal_count = 1;
    }
    else
        data->flag_meal_count = 0;
    pthread_mutex_init(&data->death_mutex, NULL);
    pthread_mutex_init(&data->print_mutex, NULL);
    return (data);
}

int create_threads(pthread_t *threads, t_philos *philos, t_args *args)
{
    int i;

    i = 0;
    while (i < args->n_philos)
    {
        pthread_create(&threads[i], NULL, (void *)routine, &philos[i]);
        i++;
    }
    i = 0;
    while (i < args->n_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    return (0);
}
int init_mutex(pthread_mutex_t *forks, int n_philos)
{
    int i;

    i = 0;
    while (i < n_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        
        i++;
    }
    return (0);
}