/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:33:37 by yel-qori          #+#    #+#             */
/*   Updated: 2025/07/05 16:56:23 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void thinking(t_philos *philo)
{
    printf("philosopher %d is thinking\n", philo->id);
}

void sleeping(t_philos *philo)
{
    printf("philosopher %d is sleeping\n", philo->id);
    usleep(philo->args->t_sleep * 1000);
}

void eating(t_philos *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
    printf("[%lu] Philosopher %d is eating\n", get_time_ms(), philo->id);

    usleep(philo->args->t_eat * 1000);
    
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);

    
}

void routine(t_philos *philo)
{
    thinking(philo);
    eating(philo);
    sleeping(philo);
}