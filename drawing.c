/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:25:23 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/09 12:48:16 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Función para limpiar la imagen
void clear_image(mlx_image_t *image, uint32_t color)
{
    int x;
    int y;
    
    y = 0;
    x = 0;
    while (y < SCREENHEIGHT)
    {
        x = 0;
        while (x < SCREENWIDTH)
        {
            mlx_put_pixel(image, x, y, color);
            x++;
        }
        y++;
    }
}

// Función para dibujar una línea vertical (de una pared)
void draw_line(t_game *game, int x, int start, int end, uint32_t color)
{
    int y;

    y = start;
    while (y < end) 
    {
        mlx_put_pixel(game->image, x, y, color);
        y++;
    }
}
