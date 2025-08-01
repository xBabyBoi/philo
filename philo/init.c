/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:02:54 by yel-qori          #+#    #+#             */
/*   Updated: 2025/08/01 10:25:10 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_philos *philos, t_args *args, pthread_mutex_t *forks)
{
	int	i;

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

t_args	*convert_args(char **av)
{
	t_args	*data;

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
	data->death_flag = 0;
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (data);
}

int	check_valid_args(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_correct_args(char **av)
{
	if (ft_atoi(av[1]) > MAX_PHILOSOPHERS || ft_atoi(av[1]) < 0
		|| check_valid_args(av[1]) == 1)
		return (ft_putstr_fd("invalid philos num\n", 2), 1);
	else if (ft_atoi(av[2]) <= 0 || check_valid_args(av[2]) == 1)
		return (ft_putstr_fd("invalid time to die\n", 2), 1);
	else if (ft_atoi(av[3]) <= 0 || check_valid_args(av[3]) == 1)
		return (ft_putstr_fd("invalid time to eat\n", 2), 1);
	else if (ft_atoi(av[4]) <= 0 || check_valid_args(av[4]) == 1)
		return (ft_putstr_fd("invalid time to sleep\n", 2), 1);
	else
		return (0);
}
