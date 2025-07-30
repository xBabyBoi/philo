/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:26:26 by yel-qori          #+#    #+#             */
/*   Updated: 2025/07/30 19:41:16 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int a)
{
	if (a >= 48 && a <= 57)
		return (1);
	return (0);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
    return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
void *safe_malloc(size_t bytes)
{
	void *res;
	
	res = malloc(bytes);
	if (!res)
		return (NULL);
	return (res);
}

long get_time_ms(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int ft_usleep(long ms)
{
	long start;

	start = get_time_ms();
	while((get_time_ms() - start) < ms)
		usleep(500);
	return (0);
}

void destory_all(char *str, t_philos * philos, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	    while (i < philos[0].args->n_philos)
    {
        pthread_mutex_destroy(&philos[i].meal_mutex);
        i++;
    }
	pthread_mutex_destroy(&philos->args->print_mutex);
	pthread_mutex_destroy(&philos->args->death_mutex);
	i = 0;
	while (i < philos[0].args->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}