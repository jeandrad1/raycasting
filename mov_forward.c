/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_forward.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:56:43 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 18:21:44 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward_y(t_game *game, double moveSpeed)
{
	if (game->worldMap[(int)(game->posY + game->dirY * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY + game->dirY * moveSpeed
			- PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY + game->dirY
			* moveSpeed)][(int)(game->posX + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY + game->dirY
			* moveSpeed)][(int)(game->posX - PLAYER_RADIUS)] == '0')
	{
		game->posY += game->dirY * moveSpeed;
	}
}

void	move_forward_x(t_game *game, double moveSpeed)
{
	if (game->worldMap[(int)(game->posY)][(int)(game->posX + game->dirX
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY)][(int)(game->posX + game->dirX
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY + PLAYER_RADIUS)][(int)(game->posX
			+ game->dirX * moveSpeed)] == '0' && game->worldMap[(int)(game->posY
			- PLAYER_RADIUS)][(int)(game->posX + game->dirX
			* moveSpeed)] == '0')
	{
		game->posX += game->dirX * moveSpeed;
	}
}

void	key_w(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	move_speed;

	game = (t_game *)param;
	move_speed = MOVE_SPEED;
	if (keydata.key == MLX_KEY_W)
	{
		move_forward_y(game, move_speed);
		move_forward_x(game, move_speed);
	}
}

void	move_forward(t_game *game, double moveSpeed)
{
	if (game->worldMap[(int)(game->posY + game->dirY * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY + game->dirY * moveSpeed
			- PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY + game->dirY
			* moveSpeed)][(int)(game->posX + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY + game->dirY
			* moveSpeed)][(int)(game->posX - PLAYER_RADIUS)] == '0')
	{
		game->posY += game->dirY * moveSpeed;
	}
	if (game->worldMap[(int)(game->posY)][(int)(game->posX + game->dirX
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY)][(int)(game->posX + game->dirX
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY + PLAYER_RADIUS)][(int)(game->posX
			+ game->dirX * moveSpeed)] == '0' && game->worldMap[(int)(game->posY
			- PLAYER_RADIUS)][(int)(game->posX + game->dirX
			* moveSpeed)] == '0')
	{
		game->posX += game->dirX * moveSpeed;
	}
}
