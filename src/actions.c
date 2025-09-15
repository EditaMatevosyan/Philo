/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmatevo <edmatevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:23:18 by edmatevo          #+#    #+#             */
/*   Updated: 2025/09/11 16:27:08 by edmatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_action(t_philo *philo, char *msg)
{
    long long now;

    pthread_mutex_lock(&philo->data->print_lock);
    now = get_time_in_ms() - philo->data->start_time;
    if (!philo->data->dead)
        printf("%lld %d %s\n", now, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_lock);
}

void take_fork(t_philo *philo)
{
    if(philo->id % 2 == 0)
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

void eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->last_meal_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->last_meal_lock);
    pthread_mutex_lock(&philo->meals_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meals_lock);
    print_action(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void sleeping(t_philo *philo)
{
    print_action(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
}

void thinking(t_philo *philo)
{
    print_action(philo, "is thinking");
}
