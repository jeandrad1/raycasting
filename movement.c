/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:27:00 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/11 18:44:24 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Función para mover al jugador
void move_player(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    double moveSpeed = MOVE_SPEED;
    double rotSpeed = ROT_SPEED;

    if (keydata.key == MLX_KEY_ESCAPE) {
        mlx_close_window(game->mlx);
        free_map(game->worldMap, game->mapHeight);
        exit(0);
    }
    if (keydata.key == MLX_KEY_W)
    {
        if (game->worldMap[(int)(game->posY)][(int)(game->posX + game->dirX * moveSpeed)] == '0')
            game->posX += game->dirX * moveSpeed;
        if (game->worldMap[(int)(game->posY + game->dirY * moveSpeed)][(int)(game->posX)] == '0')
            game->posY += game->dirY * moveSpeed;
    }
    if (keydata.key == MLX_KEY_S)
    {
        if (game->worldMap[(int)(game->posY)][(int)(game->posX - game->dirX * moveSpeed)] == '0')
            game->posX -= game->dirX * moveSpeed;
        if (game->worldMap[(int)(game->posY - game->dirY * moveSpeed)][(int)(game->posX)] == '0')
            game->posY -= game->dirY * moveSpeed;
    }
    if (keydata.key == MLX_KEY_D)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
        game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
        game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
    }
    if (keydata.key == MLX_KEY_A)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
        game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
        game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
    }
}
