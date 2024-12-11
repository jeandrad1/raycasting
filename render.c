/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:30 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/11 19:33:29 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update_and_render(void *param)
{
    t_game *game = (t_game *)param;
    clear_image(game->image, 0x000000FF); // Limpiar pantalla

    for (int x = 0; x < SCREENWIDTH; x++)
    {
        double cameraX = 2 * x / (double)SCREENWIDTH - 1;
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

        double sideDistX, sideDistY;
        int stepX, stepY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->posX - mapX) * deltaDistX;
        } 
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        } 
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
        }

        int hit = 0;
        int side; // Was a NS or a EW wall hit?
        while (hit == 0)
        {
            if (sideDistX < sideDistY) 
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } 
            else 
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (game->worldMap[mapY][mapX] > '0')
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;
                    
        int lineHeight = (int)(SCREENHEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;

        int drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawEnd >= SCREENHEIGHT)
            drawEnd = SCREENHEIGHT - 1;

        uint32_t color;
        switch (game->worldMap[mapY][mapX])
        {
            case '1': color = 0x00FF7FFF; break; // Verde
            case '3': color = 0xFF0000FF; break; // Rojo
            default: color = 0xFFFFFF; break;  // Blanco
        }

        if (side == 1) color = color / 2; // Make y-side walls darker

        draw_line(game, x, drawStart, drawEnd, color);
    }
    mlx_image_to_window(game->mlx, game->image, 0, 0);
}