/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:15:24 by yel-qori          #+#    #+#             */
/*   Updated: 2025/07/27 16:36:22 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_valid_args(char *av)
{
    int i;

    i = 0;
    while (av[i])
    {
        if (av[i] < '0' || av[i] > '9')
            return (1);
        i++;
    }
    return (0);
}
int check_correct_args(char **av)
{
    if (ft_atoi(av[1]) > MAX_PHILOSOPHERS || ft_atoi(av[1]) < 0 || check_valid_args(av[1]) == 1)
        return (ft_putstr_fd("invalid philos num\n", 2) ,1);
    else if (ft_atoi(av[2]) <= 0 || check_valid_args(av[2]) == 1)
        return (ft_putstr_fd("invalid time to die\n", 2), 1);
    else if (ft_atoi(av[3]) <= 0 || check_valid_args(av[3]) == 1)
        return (ft_putstr_fd("invalid time to eat\n", 2), 1);
    else if (ft_atoi(av[4]) <= 0 || check_valid_args(av[4]) == 1)
        return (ft_putstr_fd("invalid time to sleep\n", 2) ,1);
    else 
        return (0);
}
// av[1] : PHILO_NUM
// av[2] : time to die
// av[3] : time to eat
// av[4] : time to sleep
// av[5] : num of times each philo must eat
int main(int ac, char **av)
{
    t_args *data;
    pthread_mutex_t *forks;
    t_philos *philosophers;
    pthread_t *threads;
    

    if (ac == 5 || ac == 6)
    {
        data = convert_args(av);
        forks = safe_malloc(sizeof(pthread_mutex_t) * data->n_philos);
        init_mutex(forks, data->n_philos);
        philosophers = safe_malloc(sizeof(t_philos) * data->n_philos);
        init_philos(philosophers, data, forks);
        data->philos = philosophers;
        threads = safe_malloc(sizeof(pthread_t) * data->n_philos);
        create_threads(threads, philosophers, data);
        
    }
    else 
    {
        printf("error\n");
    }
    return (0);
}

