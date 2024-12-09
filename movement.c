/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:27:00 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/09 12:38:50 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Función para manejar las teclas (no he conseguido que vaya la mlx_key_down)
void move_player(mlx_key_data_t keydata, void *param) {
    t_game *game = (t_game *)param;
    double moveSpeed = 0.1;
    double rotSpeed = 0.05;


    if (keydata.key == MLX_KEY_ESCAPE)
    {
        mlx_close_window(game->mlx);
        exit(0);
    }
    if (keydata.key == MLX_KEY_W)
    {
        if (!game->worldMap[(int)(game->posX + game->dirX * moveSpeed)][(int)(game->posY)]) game->posX += game->dirX * moveSpeed;
        if (!game->worldMap[(int)(game->posX)][(int)(game->posY + game->dirY * moveSpeed)]) game->posY += game->dirY * moveSpeed;
    }
    if (keydata.key == MLX_KEY_S)
    {
        if (!game->worldMap[(int)(game->posX - game->dirX * moveSpeed)][(int)(game->posY)]) game->posX -= game->dirX * moveSpeed;
        if (!game->worldMap[(int)(game->posX)][(int)(game->posY - game->dirY * moveSpeed)]) game->posY -= game->dirY * moveSpeed;
    }
    if (keydata.key == MLX_KEY_A)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
        game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
        game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
    }
    if (keydata.key == MLX_KEY_D)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
        game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
        game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
    }
}
