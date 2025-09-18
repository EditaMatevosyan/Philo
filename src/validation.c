/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmatevo <edmatevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:32:34 by edmatevo          #+#    #+#             */
/*   Updated: 2025/09/18 18:47:44 by edmatevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_num(char *str)
{
	long	num;

	if (!is_digit(str))
		return (0);
	num = ft_atol(str);
	if (num < 1 || num > INT_MAX)
		return (0);
	return (1);
}

int	validate(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments!\n");
		return (0);
	}
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 1000)
	{
		printf("Incorrect number of philosophers!\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_num(argv[i]))
		{
			printf("Invalid argument at position %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}
