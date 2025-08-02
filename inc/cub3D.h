/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:48:47 by hbousset          #+#    #+#             */
/*   Updated: 2025/08/02 20:15:52 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mylib/myLib.h"
# include "../minilibx/mlx.h"

typedef struct s_var
{
	int		ac;
	char	**av;
	void	*mlx;
	void	*win;
}	t_var;

#endif
