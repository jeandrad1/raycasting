/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:25:23 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/09 12:31:30 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Función para limpiar la imagen
void clear_image(mlx_image_t *image, uint32_t color)
{
    for (int y = 0; y < SCREENHEIGHT; y++) {
        for (int x = 0; x < SCREENWIDTH; x++) {
            mlx_put_pixel(image, x, y, color);
        }
    }
}

// Función para dibujar una línea vertical (de una pared)
void draw_line(t_game *game, int x, int start, int end, uint32_t color)
{
    for (int y = start; y < end; y++) {
        mlx_put_pixel(game->image, x, y, color);
    }
}
