/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:27:00 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 18:22:59 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	escape_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		free_map(game->worldMap, game->mapHeight);
		exit(0);
	}
}

void	move_backward(t_game *game, double moveSpeed)
{
	if (game->worldMap[(int)(game->posY - game->dirY * moveSpeed
			+ PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY - game->dirY * moveSpeed
			- PLAYER_RADIUS)][(int)(game->posX)] == '0'
		&& game->worldMap[(int)(game->posY - game->dirY
			* moveSpeed)][(int)(game->posX + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY - game->dirY
			* moveSpeed)][(int)(game->posX - PLAYER_RADIUS)] == '0')
	{
		game->posY -= game->dirY * moveSpeed;
	}
	if (game->worldMap[(int)(game->posY)][(int)(game->posX - game->dirX
			* moveSpeed + PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY)][(int)(game->posX - game->dirX
			* moveSpeed - PLAYER_RADIUS)] == '0'
		&& game->worldMap[(int)(game->posY + PLAYER_RADIUS)][(int)(game->posX
			- game->dirX * moveSpeed)] == '0' && game->worldMap[(int)(game->posY
			- PLAYER_RADIUS)][(int)(game->posX - game->dirX
			* moveSpeed)] == '0')
	{
		game->posX -= game->dirX * moveSpeed;
	}
}

void	foward_and_back_mov(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	move_speed;

	game = (t_game *)param;
	move_speed = MOVE_SPEED;
	if (keydata.key == MLX_KEY_W)
		move_forward(game, move_speed);
	if (keydata.key == MLX_KEY_S)
		move_backward(game, move_speed);
}

// Función para mover al jugador
void	move_player(mlx_key_data_t keydata, void *param)
{
	escape_key(keydata, param);
	foward_and_back_mov(keydata, param);
	side_mov(keydata, param);
	turn_mov(keydata, param);
}
