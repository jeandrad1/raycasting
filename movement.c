/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:27:00 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 17:47:02 by jeandrad         ###   ########.fr       */
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

void	key_w(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	moveSpeed;

	game = (t_game *)param;
	moveSpeed = MOVE_SPEED;
	if (keydata.key == MLX_KEY_W)
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
			&& game->worldMap[(int)(game->posY
				+ PLAYER_RADIUS)][(int)(game->posX + game->dirX
				* moveSpeed)] == '0' && game->worldMap[(int)(game->posY
				- PLAYER_RADIUS)][(int)(game->posX + game->dirX
				* moveSpeed)] == '0')
		{
			game->posX += game->dirX * moveSpeed;
		}
	}
}

void	foward_and_back_mov(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	moveSpeed;

	game = (t_game *)param;
	moveSpeed = MOVE_SPEED;
	key_w(keydata, game);
	if (keydata.key == MLX_KEY_S)
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
			&& game->worldMap[(int)(game->posY
				+ PLAYER_RADIUS)][(int)(game->posX - game->dirX
				* moveSpeed)] == '0' && game->worldMap[(int)(game->posY
				- PLAYER_RADIUS)][(int)(game->posX - game->dirX
				* moveSpeed)] == '0')
		{
			game->posX -= game->dirX * moveSpeed;
		}
	}
}

void	key_a(mlx_key_data_t keydata, void *param)
{
	double	moveSpeed;
	t_game	*game;

	moveSpeed = MOVE_SPEED;
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_A)
	{
		if (game->worldMap[(int)(game->posY)][(int)(game->posX - game->planeX
				* moveSpeed + PLAYER_RADIUS)] == '0'
			&& game->worldMap[(int)(game->posY)][(int)(game->posX - game->planeX
				* moveSpeed - PLAYER_RADIUS)] == '0'
			&& game->worldMap[(int)(game->posY
				+ PLAYER_RADIUS)][(int)(game->posX - game->planeX
				* moveSpeed)] == '0' && game->worldMap[(int)(game->posY
				- PLAYER_RADIUS)][(int)(game->posX - game->planeX
				* moveSpeed)] == '0')
		{
			game->posX -= game->planeX * moveSpeed;
		}
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
}

void	move_right_planeX(t_game *game, double moveSpeed)
{
    if (game->worldMap[(int)(game->posY)][(int)(game->posX + game->planeX
            * moveSpeed + PLAYER_RADIUS)] == '0'
        && game->worldMap[(int)(game->posY)][(int)(game->posX + game->planeX
            * moveSpeed - PLAYER_RADIUS)] == '0'
        && game->worldMap[(int)(game->posY + PLAYER_RADIUS)][(int)(game->posX + game->planeX
            * moveSpeed)] == '0' && game->worldMap[(int)(game->posY - PLAYER_RADIUS)]\
			[(int)(game->posX + game->planeX
            * moveSpeed)] == '0')
    {
        game->posX += game->planeX * moveSpeed;
    }
}

void	move_right_planeY(t_game *game, double moveSpeed)
{
    if (game->worldMap[(int)(game->posY + game->planeY * moveSpeed
            + PLAYER_RADIUS)][(int)(game->posX)] == '0'
        && game->worldMap[(int)(game->posY + game->planeY * moveSpeed
            - PLAYER_RADIUS)][(int)(game->posX)] == '0'
        && game->worldMap[(int)(game->posY + game->planeY *
		moveSpeed)][(int)(game->posX + PLAYER_RADIUS)] == '0'
        && game->worldMap[(int)(game->posY + game->planeY *
		moveSpeed)][(int)(game->posX - PLAYER_RADIUS)] == '0')
    {
        game->posY += game->planeY * moveSpeed;
    }
}

void	side_mov(mlx_key_data_t keydata, void *param)
{
    t_game	*game;
    double	moveSpeed;

    game = (t_game *)param;
    moveSpeed = MOVE_SPEED;
    key_a(keydata, game);
    if (keydata.key == MLX_KEY_D)
    {
        move_right_planeX(game, moveSpeed);
        move_right_planeY(game, moveSpeed);
    }
}

void turn_left(t_game *game, double rotSpeed)
{
    t_old old = {game->dirX, game->planeX};
    game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
    game->dirY = old.dirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
    game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
    game->planeY = old.planeX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
}

void turn_right(t_game *game, double rotSpeed)
{
    t_old old = {game->dirX, game->planeX};
    game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
    game->dirY = old.dirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
    game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
    game->planeY = old.planeX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
}

void turn_mov(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    double rotSpeed = ROT_SPEED;

    if (keydata.key == MLX_KEY_LEFT)
        turn_left(game, rotSpeed);
    if (keydata.key == MLX_KEY_RIGHT)
        turn_right(game, rotSpeed);
}

// Función para mover al jugador
void	move_player(mlx_key_data_t keydata, void *param)
{
	escape_key(keydata, param);
	foward_and_back_mov(keydata, param);
	side_mov(keydata, param);
	turn_mov(keydata, param);
}
