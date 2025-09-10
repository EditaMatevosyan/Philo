/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmatevo <edmatevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:36:20 by edmatevo          #+#    #+#             */
/*   Updated: 2025/09/10 19:52:10 by edmatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init(int argc, char *argv[], t_data *data)
{
    data->nb_philos = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if(data->nb_philos <= 0 || data->time_to_die < 0 ||
        data->time_to_eat < 0 || data->time_to_sleep < 0)
        return 1;
    if(argc == 6)
    {
        data->must_eat = ft_atol(argv[5]);
        if(data->must_eat <= 0)
            return 1;
    }
    else
        data->must_eat = -1;
    data->dead = 0;
    data->start_time = get_time_in_ms();    
    return 0;
}

int init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
    if(!data->forks)
        return 1;
    i = 0;
    while(i < data->nb_philos)
    {
        if(pthread_mutex_init(&data->forks[i], NULL) != 0)
            return 1;
        i++;
    }
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
        return 1;
    if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
        return 1;
    return 0;
}

int init_philos(t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * data->nb_philos);
    if(!data->philos)
        return 1;
    i = 0;
    
    while (i < data->nb_philos)
    {
        data->philos[i].id = i+1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal = data->start_time;
        data->philos[i].data = data;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
        pthread_mutex_init(&data->philos[i].last_meal_lock, NULL);
        pthread_mutex_init(&data->philos[i].meals_lock, NULL);
        i++;
    }
    return 0;
}

int init_all(int argc, char *argv[], t_data *data)
{
    if (init(argc, argv, data))
        return 1;
    if (init_mutexes(data))
        return 1;
    if (init_philos(data))
        return 1;
    return 0;
}

void cleanup(t_data *data)
{
    int i;

    if (data->philos)
    {
        i = 0;
        while (i < data->nb_philos)
        {
            pthread_mutex_destroy(&data->philos[i].last_meal_lock);
            pthread_mutex_destroy(&data->philos[i].meals_lock);
            i++;
        }
        free(data->philos);
    }
    if (data->forks)
    {
        i = 0;
        while (i < data->nb_philos)
            pthread_mutex_destroy(&data->forks[i++]);
        free(data->forks);
    }
    pthread_mutex_destroy(&data->dead_lock);
    pthread_mutex_destroy(&data->print_lock);
    free(data);
}

