/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmatevo <edmatevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:21:32 by edmatevo          #+#    #+#             */
/*   Updated: 2025/09/10 19:51:02 by edmatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time_in_ms(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->data->nb_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return NULL;
    }
    while(!philo->data->dead)
    {
        take_fork(philo);
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return NULL;
}

int check_death(t_philo *philo)
{
    long long now;

    pthread_mutex_lock(&philo->last_meal_lock);
    now = get_time_in_ms();
    if (now - philo->last_meal > philo->data->time_to_die)
    {
        pthread_mutex_unlock(&philo->last_meal_lock);
        pthread_mutex_lock(&philo->data->dead_lock);
        if (!philo->data->dead) 
        {
            philo->data->dead = 1;
            pthread_mutex_unlock(&philo->data->dead_lock);
            print_action(philo, "died");
        }
        else
            pthread_mutex_unlock(&philo->data->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->last_meal_lock);
    return (0);
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (!data->dead)
    {
        i = 0;
        while (i < data->nb_philos && !data->dead)
        {
            if (check_death(&data->philos[i]))
                return NULL;
            i++;
        }
        usleep(1000); 
    }
    return NULL;
}
