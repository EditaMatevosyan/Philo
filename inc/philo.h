/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmatevo <edmatevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:18:31 by edmatevo              #+#    #+#             */
/*   Updated: 2025/09/10 19:19:20 by edmatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

typedef struct  s_philo t_philo;

typedef struct s_data
{
    int nb_philos;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
    int must_eat;
    int dead;
    long long start_time;
    pthread_mutex_t dead_lock;
    pthread_mutex_t print_lock;
    pthread_mutex_t *forks;
    t_philo *philos;
} t_data;

typedef struct s_philo
{
    int id;
    int meals_eaten;
    long long   last_meal;
    pthread_t thread_id;
    pthread_mutex_t last_meal_lock;
    pthread_mutex_t meals_lock;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
} t_philo;


long ft_atol(char *num);
int validate(int argc, char *argv[]);
int init(int argc, char *argv[], t_data *data);
int init_mutexes(t_data *data);
int init_philos(t_data *data);
int init_all(int argc, char *argv[], t_data *data);
void cleanup(t_data *data);
// int start_thread(t_data *data);
// int join_thread(t_data *data);
long long get_time_in_ms(void);
void *philo_routine(void *arg);
void *monitor_routine(void *arg);
void smart_usleep(t_philo *philo, int time_ms);


void print_action(t_philo *philo, char *msg);
void take_fork(t_philo *philo);
void eating(t_philo *philo);
void thinking(t_philo *philo);
void sleeping(t_philo *philo);


#endif
