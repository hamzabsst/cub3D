/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchaman <abchaman@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:01:28 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/08 02:43:25 by abchaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"


int check_name(char *str)
{
    int i;
    int last;
    
    i = 0;
    last = -1;
    if (!str || !str[0])
        return (1);
    while (str[i])
    {
        if (str[i] == '.' && str[i + 1] == '.')
            return (1);
        if (str[i] == '.')
            last = i;
        i++;
    }
    if (last <= 0)
        return (1);
    if (ft_strncmp(&str[last], ".cub", 4))
            return (1);
    if (str[last + 4] != '\0')
        return (1);
    return (0);
}
