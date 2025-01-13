/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_mov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:58:52 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 18:32:20 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_left(t_game *game, double rotSpeed)
{
	t_old	old;

	old.dirX = game->dirX;
	old.planeX = game->planeX;
	game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
	game->dirY = old.dirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
	game->planeX = game->planeX * cos(-rotSpeed) - game->planeY
		* sin(-rotSpeed);
	game->planeY = old.planeX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
}

void	turn_right(t_game *game, double rotSpeed)
{
	t_old	old;

	old.dirX = game->dirX;
	old.planeX = game->planeX;
	game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
	game->dirY = old.dirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
	game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
	game->planeY = old.planeX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
}

void	turn_mov(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	rot_speed;

	game = (t_game *)param;
	rot_speed = ROT_SPEED;
	if (keydata.key == MLX_KEY_LEFT)
		turn_left(game, rot_speed);
	if (keydata.key == MLX_KEY_RIGHT)
		turn_right(game, rot_speed);
}
