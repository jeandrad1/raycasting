/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:27:00 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/11 15:26:38 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void escape_key(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (keydata.key == MLX_KEY_ESCAPE)
    {
        mlx_close_window(game->mlx);
        free_map(game->worldMap, game->mapHeight);
        exit(0);
    }
}

void foward_and_back_mov(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    double moveSpeed = MOVE_SPEED;

    if (keydata.key == MLX_KEY_W)
    {
        if (game->worldMap[(int)(game->posY + game->dirY * moveSpeed + PLAYER_RADIUS)][(int)(game->posX + game->dirX * moveSpeed + PLAYER_RADIUS)] == '0' &&
            game->worldMap[(int)(game->posY + game->dirY * moveSpeed - PLAYER_RADIUS)][(int)(game->posX + game->dirX * moveSpeed - PLAYER_RADIUS)] == '0')
        {
            game->posX += game->dirX * moveSpeed;
            game->posY += game->dirY * moveSpeed;
        }
    }
    if (keydata.key == MLX_KEY_S)
    {
        if (game->worldMap[(int)(game->posY - game->dirY * moveSpeed + PLAYER_RADIUS)][(int)(game->posX - game->dirX * moveSpeed + PLAYER_RADIUS)] == '0' &&
            game->worldMap[(int)(game->posY - game->dirY * moveSpeed - PLAYER_RADIUS)][(int)(game->posX - game->dirX * moveSpeed - PLAYER_RADIUS)] == '0')
        {
            game->posX -= game->dirX * moveSpeed;
            game->posY -= game->dirY * moveSpeed;
        }
    }
}

void side_mov(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    double moveSpeed = MOVE_SPEED;

    if (keydata.key == MLX_KEY_A)
    {
        if (game->worldMap[(int)(game->posY - game->planeY * moveSpeed + PLAYER_RADIUS)][(int)(game->posX - game->planeX * moveSpeed + PLAYER_RADIUS)] == '0' &&
            game->worldMap[(int)(game->posY - game->planeY * moveSpeed - PLAYER_RADIUS)][(int)(game->posX - game->planeX * moveSpeed - PLAYER_RADIUS)] == '0')
        {
            game->posX -= game->planeX * moveSpeed;
            game->posY -= game->planeY * moveSpeed;
        }
    }
    if (keydata.key == MLX_KEY_D)
    {
        if (game->worldMap[(int)(game->posY + game->planeY * moveSpeed + PLAYER_RADIUS)][(int)(game->posX + game->planeX * moveSpeed + PLAYER_RADIUS)] == '0' &&
            game->worldMap[(int)(game->posY + game->planeY * moveSpeed - PLAYER_RADIUS)][(int)(game->posX + game->planeX * moveSpeed - PLAYER_RADIUS)] == '0')
        {
            game->posX += game->planeX * moveSpeed;
            game->posY += game->planeY * moveSpeed;
        }
    }
}

void turn_mov(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    double rotSpeed = ROT_SPEED;
    
    if (keydata.key == MLX_KEY_LEFT)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
        game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
        game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
    }
    if (keydata.key == MLX_KEY_RIGHT)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
        game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
        game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
    }
}

// Función para mover al jugador
void move_player(mlx_key_data_t keydata, void *param)
{
    escape_key(keydata, param);
    foward_and_back_mov(keydata, param);
    side_mov(keydata, param);
    turn_mov(keydata, param);
}
