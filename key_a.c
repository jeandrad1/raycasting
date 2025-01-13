/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:15:23 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 18:15:42 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	move_left_planeX(t_game *game, double moveSpeed)
{
    if (game->worldMap[(int)(game->posY)][(int)(game->posX - game->planeX *
		moveSpeed + PLAYER_RADIUS)] == '0'
        && game->worldMap[(int)(game->posY)][(int)(game->posX - game->planeX *
		moveSpeed - PLAYER_RADIUS)] == '0'
        && game->worldMap[(int)(game->posY + PLAYER_RADIUS)][(int)(game->posX - game->planeX *
		moveSpeed)] == '0'
        && game->worldMap[(int)(game->posY - PLAYER_RADIUS)][(int)(game->posX - game->planeX *
		moveSpeed)] == '0')
    {
        game->posX -= game->planeX * moveSpeed;
    }
}

void	move_left_planeY(t_game *game, double moveSpeed)
{
    if (game->worldMap[(int)(game->posY - game->planeY *
		moveSpeed + PLAYER_RADIUS)][(int)(game->posX)] == '0'
        && game->worldMap[(int)(game->posY - game->planeY *
		moveSpeed - PLAYER_RADIUS)][(int)(game->posX)] == '0'
        && game->worldMap[(int)(game->posY - game->planeY *
		moveSpeed)][(int)(game->posX + PLAYER_RADIUS)] == '0'
        && game->worldMap[(int)(game->posY - game->planeY *
		moveSpeed)][(int)(game->posX - PLAYER_RADIUS)] == '0')
    {
        game->posY -= game->planeY * moveSpeed;
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
        move_left_planeX(game, moveSpeed);
        move_left_planeY(game, moveSpeed);
    }
}
