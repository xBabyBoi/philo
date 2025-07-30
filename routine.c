/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:33:37 by yel-qori          #+#    #+#             */
/*   Updated: 2025/07/30 17:30:04 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void thinking(t_philos *philo)
{
    safe_print(philo, "philosopher is thinking\n");
}

void sleeping(t_philos *philo)
{
    safe_print(philo, "philosopher is sleeping\n");
    ft_usleep(philo->args->t_sleep);
}

void eating(t_philos *philo)
{
    if (philo->args->n_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken left fork\n");
        ft_usleep(philo->args->t_die);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken left fork\n");
        pthread_mutex_lock(philo->right_fork);
        safe_print(philo, "has taken right fork\n");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        safe_print(philo, "has taken right fork\n");
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken left fork\n");
    }
    safe_print(philo, "is eating\n");
    pthread_mutex_lock(&philo->meal_mutex);
    philo->meals_counter++;
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->meal_mutex);
    ft_usleep(philo->args->t_eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

int all_meals_completed(t_philos *philos, int n_philos)
{
    int i;
    int completed_meals;
    
    i = 0;
    completed_meals = 0;
    if (philos[0].args->flag_meal_count != 1)
        return (0);
    while (n_philos > i)
    {
        pthread_mutex_lock(&philos[i].meal_mutex);
        if (philos[i].meals_counter >= philos[i].args->meal_count)
            completed_meals++;
        pthread_mutex_unlock(&philos[i].meal_mutex);
        i++;
    }
    return (completed_meals == n_philos);
}

int is_dead_global(t_args *args)
{
    int dead;
    
    pthread_mutex_lock(&args->death_mutex);
    dead = args->death_flag;
    pthread_mutex_unlock(&args->death_mutex);
    return (dead);
}

void set_death_flag(t_args *args)
{
    pthread_mutex_lock(&args->death_mutex);
    args->death_flag = 1;
    pthread_mutex_unlock(&args->death_mutex);
}


int is_dead(t_philos *philo)
{
    long current_time;
    long time_since_meal;
    
    current_time = get_time_ms();
    
    pthread_mutex_lock(&philo->meal_mutex);
    time_since_meal = current_time - philo->last_meal_time;
    pthread_mutex_unlock(&philo->meal_mutex);
    
    if (time_since_meal > philo->args->t_die)
    {
        set_death_flag(philo->args); 
        printf("%ld %d died\n", current_time - philo->args->start_time, philo->id);
        return (1);
    }
    return (0);
}
void safe_print(t_philos *philo, char *action)
{
    long relative_time;
    
    pthread_mutex_lock(&philo->args->print_mutex);
    if (!is_dead_global(philo->args))
    {
        relative_time = get_time_ms() - philo->args->start_time;
        printf("%ld %d %s", relative_time, philo->id, action);
    }
    pthread_mutex_unlock(&philo->args->print_mutex);
}

void routine(t_philos *philo)
{
    if (philo->id % 2 == 0)
        ft_usleep(1);
        
    while (!is_dead_global(philo->args))
    {
        thinking(philo);
        if (is_dead_global(philo->args))
            break;
            
        eating(philo);
        if (is_dead_global(philo->args))
            break;
        if (philo->args->flag_meal_count)
        {
            pthread_mutex_lock(&philo->meal_mutex);
            int meals_done = philo->meals_counter >= philo->args->meal_count;
            pthread_mutex_unlock(&philo->meal_mutex);
            
            if (meals_done)
                break; // This philosopher is done
        }
        sleeping(philo);
    }
}
