/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:33:37 by yel-qori          #+#    #+#             */
/*   Updated: 2025/08/01 10:32:53 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philos *philo)
{
	safe_print(philo, "philosopher is thinking\n");
}

void	sleeping(t_philos *philo)
{
	safe_print(philo, "philosopher is sleeping\n");
	ft_usleep(philo->args->t_sleep);
}

void	take_forks(t_philos *philo)
{
	if (philo->args->n_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken left fork\n");
		ft_usleep(philo->args->t_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
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
}

void	eating(t_philos *philo)
{
	take_forks(philo);
	if (philo->args->n_philos == 1)
		return ;
	safe_print(philo, "is eating\n");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_counter++;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->args->t_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	routine(t_philos *philo)
{
	int	meals_done;

	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_dead_global(philo->args))
	{
		thinking(philo);
		if (is_dead_global(philo->args))
			break ;
		eating(philo);
		if (is_dead_global(philo->args))
			break ;
		if (philo->args->flag_meal_count)
		{
			pthread_mutex_lock(&philo->meal_mutex);
			meals_done = philo->meals_counter >= philo->args->meal_count;
			pthread_mutex_unlock(&philo->meal_mutex);
			if (meals_done)
				break ;
		}
		sleeping(philo);
	}
}
