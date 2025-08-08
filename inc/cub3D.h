/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchaman <abchaman@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:47 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/08 02:12:14 by abchaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mylib/myLib.h"
# include "../minilibx/mlx.h"
# include <stdio.h>

typedef struct s_var
{
	int		ac;
	char	**av;
	void	*mlx;
	void	*win;
}	t_var;

int	check_name(char *str);
#endif
