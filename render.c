/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:30 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/09 12:46:27 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Función para actualizar y renderizar la imagen
void update_and_render(void *param)
{
    t_game *game = (t_game *)param;
    clear_image(game->image, 0x000000FF); // Limpiar pantalla

    for (int x = 0; x < SCREENWIDTH; x++) {
        // Calculamos la dirección del rayo
        double cameraX = 2 * x / (double)SCREENWIDTH - 1; // Mapeo de la pantalla en [-1, 1]
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        // Posición inicial del rayo
        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

        // Longitudes del rayo
        double sideDistX, sideDistY;

        // Dirección de los pasos en cada eje
        int stepX, stepY;

        // Variables de distancia
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        // Determinar el paso en cada eje
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->posX - mapX) * deltaDistX;
        } else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        } else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
        }

        // Realizar el "DDA" (Digital Differential Analyzer) para encontrar la intersección del rayo con las paredes
        int hit = 0;
        while (hit == 0)
        {
            // Si el rayo golpea una pared en el eje X
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                if (game->worldMap[mapX][mapY] > 0) hit = 1;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                if (game->worldMap[mapX][mapY] > 0) hit = 1;
            }
        }

        // Calcular la distancia hasta el punto de intersección del rayo
        if (sideDistX < sideDistY)
            perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;


        // Calcular la altura de la pared
        int lineHeight = (int)(SCREENHEIGHT / perpWallDist);

        // Calcular el inicio y final de la pared en la pantalla
        int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawEnd >= SCREENHEIGHT) drawEnd = SCREENHEIGHT - 1;

        // Determinar el color de la pared
        uint32_t color;
        switch (game->worldMap[mapX][mapY])
        {
            case 1: color = 0x00FF7FFF; break; // Paredes verdes
            default: color = 0xFFFFFF; break;  // Blanco
        }
        // Dibujar la pared
        draw_line(game, x, drawStart, drawEnd, color);
    }
    mlx_image_to_window(game->mlx, game->image, 0, 0); // Mostrar la imagen en la ventana
}
