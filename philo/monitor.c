/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 10:21:50 by yel-qori          #+#    #+#             */
/*   Updated: 2025/08/01 10:31:18 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philosopher_death(t_philos *philos, int i)
{
	long	last_meal;

	pthread_mutex_lock(&philos[i].meal_mutex);
	last_meal = philos[i].last_meal_time;
	if (get_time_ms() - last_meal > philos->args->t_die)
	{
		safe_print(&philos[i], "is dead");
		set_death_flag(philos->args);
		pthread_mutex_unlock(&philos[i].meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos[i].meal_mutex);
	return (0);
}

void	monitoring(t_philos *philos)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < philos->args->n_philos)
		{
			if (check_philosopher_death(philos, i))
				return ;
			i++;
		}
		if (philos->args->flag_meal_count && all_meals_completed(philos,
				philos->args->n_philos))
		{
			set_death_flag(philos->args);
			return ;
		}
		usleep(1000);
	}
}

void	safe_print(t_philos *philo, char *action)
{
	long	relative_time;

	pthread_mutex_lock(&philo->args->print_mutex);
	if (!is_dead_global(philo->args))
	{
		relative_time = get_time_ms() - philo->args->start_time;
		printf("%ld %d %s", relative_time, philo->id, action);
	}
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	set_death_flag(t_args *args)
{
	pthread_mutex_lock(&args->death_mutex);
	args->death_flag = 1;
	pthread_mutex_unlock(&args->death_mutex);
}

int	all_meals_completed(t_philos *philos, int n_philos)
{
	int	i;
	int	completed_meals;

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
