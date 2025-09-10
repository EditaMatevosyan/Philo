/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:32:22 by user              #+#    #+#             */
/*   Updated: 2025/09/08 10:36:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long ft_atol(char *num)
{
    int i;
    int sign;
    long result;

    i = 0;
    result = 0;
    sign = 1;
    while(num[i] == ' '  || (num[i] >= 9 && num[i] <= 13))
        i++;
    if(num[i] == '+' || num[i] == '-')
    {
        if(num[i] == '-')
            sign = -1;
        i++;
    }
    while (num[i] && (num[i] >= '0' && num[i] <= '9'))
    {
        result = result * 10 + (num[i] - '0');
        i++;
    }
    return(result * sign);
}