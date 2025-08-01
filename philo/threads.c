/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 10:24:07 by yel-qori          #+#    #+#             */
/*   Updated: 2025/08/01 10:33:17 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(pthread_t *threads, t_philos *philos, t_args *args,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < args->n_philos)
	{
		if (pthread_create(&threads[i], NULL, (void *)routine, &philos[i]) != 0)
			destory_all("pthread_create failed\n", philos, forks);
		i++;
	}
	i = 0;
	monitoring(philos);
	while (i < args->n_philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
			destory_all("pthread_join failed\n", philos, forks);
		i++;
	}
	return (0);
}

int	init_mutex(pthread_mutex_t *forks, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (0);
}

int	is_dead_global(t_args *args)
{
	int	dead;

	pthread_mutex_lock(&args->death_mutex);
	dead = args->death_flag;
	pthread_mutex_unlock(&args->death_mutex);
	return (dead);
}

int	is_dead(t_philos *philo)
{
	long	current_time;
	long	time_since_meal;

	current_time = get_time_ms();
	pthread_mutex_lock(&philo->meal_mutex);
	time_since_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_since_meal > philo->args->t_die)
	{
		set_death_flag(philo->args);
		printf("%ld %d died\n", current_time - philo->args->start_time,
			philo->id);
		return (1);
	}
	return (0);
}
