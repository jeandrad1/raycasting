/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:19:59 by jeandrad          #+#    #+#             */
/*   Updated: 2024/11/29 08:32:51 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

#define WIDTH 800
#define HEIGHT 600

void draw_square(mlx_image_t* img, int x, int y, int size, uint32_t color)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

int main(void)
{
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Square Example", true);
    if (!mlx)
        return EXIT_FAILURE;
    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
    {
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    draw_square(img, 100, 100, 200, 0xFF0000FF);

    mlx_image_to_window(mlx, img, 0, 0);

    mlx_loop(mlx);

    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}