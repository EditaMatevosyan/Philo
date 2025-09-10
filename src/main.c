/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:32:03 by user              #+#    #+#             */
/*   Updated: 2025/09/09 15:35:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_data data;

    if (!validate(argc, argv))
        return 1;
    if (init_all(argc, argv, &data))
        return 1;
    cleanup(&data);
    return 0;
}