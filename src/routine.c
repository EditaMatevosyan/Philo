/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmatevo <edmatevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:21:32 by edmatevo          #+#    #+#             */
/*   Updated: 2025/09/18 19:06:39 by edmatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_usleep(t_philo *philo, int time_ms)
{
	long long	now;

	now = get_time_in_ms();
	while (get_time_in_ms() - now < time_ms)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		usleep(100);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 1)
		usleep(1000);
	while (!philo->data->dead)
	{
		take_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	check_death(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->last_meal_lock);
	now = get_time_in_ms();
	if (now - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_lock);
		pthread_mutex_lock(&philo->data->print_lock);
		if (!philo->data->dead)
		{
			printf("%lld %d died\n", now - philo->data->start_time, philo->id);
			philo->data->dead = 1;
		}
		pthread_mutex_unlock(&philo->data->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_lock);
	return (0);
}

static int	all_philos_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].meals_lock);
		if (data->philos[i].meals_eaten < data->must_eat)
		{
			pthread_mutex_unlock(&data->philos[i].meals_lock);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meals_lock);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->dead)
	{
		i = 0;
		while (i < data->nb_philos && !data->dead)
		{
			if (check_death(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (data->must_eat > 0 && all_philos_full(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
