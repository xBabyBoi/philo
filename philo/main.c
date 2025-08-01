/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:15:24 by yel-qori          #+#    #+#             */
/*   Updated: 2025/08/01 10:46:17 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_program(int ac, char **av, t_init_data *init)
{
	if (ac != 5 && ac != 6)
		return (write(2, "invalid arguments\n", 18));
	if (check_correct_args(av) == 1)
		return (1);
	init->data = convert_args(av);
	if (!init->data)
		return (write(2, "memory allocation failed\n", 25), 1);
	init->forks = safe_malloc(sizeof(pthread_mutex_t) * init->data->n_philos);
	if (!init->forks)
		return (free(init->data), write(2, "memory allocation failed\n", 25),
			1);
	init_mutex(init->forks, init->data->n_philos);
	init->philosophers = safe_malloc(sizeof(t_philos) * init->data->n_philos);
	if (!init->philosophers)
		return (destory_all(NULL, NULL, init->forks), free(init->forks),
			free(init->data), write(2, "memory allocation failed\n", 25), 1);
	init_philos(init->philosophers, init->data, init->forks);
	init->data->philos = init->philosophers;
	init->threads = safe_malloc(sizeof(pthread_t) * init->data->n_philos);
	if (!init->threads)
		return (destory_all(NULL, init->philosophers, init->forks),
			free(init->philosophers), free(init->forks), free(init->data),
			write(2, "memory allocation failed\n", 25), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_init_data	init;

	if (init_program(ac, av, &init) != 0)
		return (1);
	create_threads(init.threads, init.philosophers, init.data, init.forks);
	destory_all(NULL, init.philosophers, init.forks);
	free(init.threads);
	free(init.philosophers);
	free(init.forks);
	free(init.data);
	return (0);
}
