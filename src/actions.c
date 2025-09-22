/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmatevo <edmatevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:23:18 by edmatevo          #+#    #+#             */
/*   Updated: 2025/09/22 14:07:47 by edmatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long long	now;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->dead)
	{
		now = get_time_in_ms() - philo->data->start_time;
		printf("%lld %d %s\n", now, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_lock);
	pthread_mutex_lock(&philo->meals_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_lock);
	print_action(philo, "is eating");
	my_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	my_usleep(philo, philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
}
