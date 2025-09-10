/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmatevo <edmatevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:32:03 by edmatevo          #+#    #+#             */
/*   Updated: 2025/09/10 19:51:51 by edmatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_data data;
    int i;
    pthread_t monitor;

    if (!validate(argc, argv))
        return 1;
    if (init_all(argc, argv, &data))
        return 1;
    i = 0;
    while(i < data.nb_philos)
    {
        if(pthread_create(&data.philos[i].thread_id, NULL, philo_routine, 
            &data.philos[i]) != 0)
            return 1;
        i++;
    }
    pthread_create(&monitor, NULL, monitor_routine, &data);
    i = 0;
    while (i < data.nb_philos)
        pthread_join(data.philos[i++].thread_id, NULL);
    pthread_join(monitor, NULL);
    cleanup(&data);
    return 0;
}
