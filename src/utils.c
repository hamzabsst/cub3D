/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:01:40 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/10 16:01:45 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_error(char *msg)
{
	char	*full;

	full = ft_strjoin("Error: ", msg);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(full);
	return (1);
}
