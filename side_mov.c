/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_mov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:00:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 18:29:13 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_right_plane_x(t_game *game, double moveSpeed)
{
	if (game->worldMap[(int)(game->posY)][(int)(game->posX + game->planeX
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY)][(int)(game->posX + game->planeX
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY + PLAYER_RADIUS)][(int)(game->posX
			+ game->planeX * moveSpeed)] == '0'
		&& game->worldMap[(int)(game->posY - PLAYER_RADIUS)][(int)(game->posX
			+ game->planeX * moveSpeed)] == '0')
	{
		game->posX += game->planeX * moveSpeed;
	}
}

void	move_right_plane_y(t_game *game, double moveSpeed)
{
	if (game->worldMap[(int)(game->posY + game->planeY * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY + game->planeY * moveSpeed
			- PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY + game->planeY
			* moveSpeed)][(int)(game->posX + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY + game->planeY
			* moveSpeed)][(int)(game->posX - PLAYER_RADIUS)] == '0')
	{
		game->posY += game->planeY * moveSpeed;
	}
}

void	side_mov(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	move_speed;

	game = (t_game *)param;
	move_speed = MOVE_SPEED;
	key_a(keydata, game);
	if (keydata.key == MLX_KEY_D)
	{
		move_right_plane_x(game, move_speed);
		move_right_plane_y(game, move_speed);
	}
}
