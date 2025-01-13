/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:15:23 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 18:19:57 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Aux function to move the player to the left
// in the X axis
void	move_left_plane_x(t_game *game, double moveSpeed)
{
	if (game->worldMap[(int)(game->posY)][(int)(game->posX - game->planeX
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY)][(int)(game->posX - game->planeX
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY + PLAYER_RADIUS)][(int)(game->posX
			- game->planeX * moveSpeed)] == '0'
		&& game->worldMap[(int)(game->posY - PLAYER_RADIUS)][(int)(game->posX
			- game->planeX * moveSpeed)] == '0')
	{
		game->posX -= game->planeX * moveSpeed;
	}
}

// Aux function to move the player to the left
// in the Y axis
void	move_left_plane_y(t_game *game, double moveSpeed)
{
	if (game->worldMap[(int)(game->posY - game->planeY * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY - game->planeY * moveSpeed
			- PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY - game->planeY
			* moveSpeed)][(int)(game->posX + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY - game->planeY
			* moveSpeed)][(int)(game->posX - PLAYER_RADIUS)] == '0')
	{
		game->posY -= game->planeY * moveSpeed;
	}
}

// Function to move the player to the left
void	key_a(mlx_key_data_t keydata, void *param)
{
	double	move_speed;
	t_game	*game;

	move_speed = MOVE_SPEED;
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_A)
	{
		move_left_plane_x(game, move_speed);
		move_left_plane_y(game, move_speed);
	}
}
