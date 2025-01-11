/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:30 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/11 14:15:22 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_wall_with_texture(t_game *game, t_ray *ray, int x, t_lines *lines)
{
    mlx_texture_t *texture;
    double wallX;
    int texX, texY;
    int y;
    uint32_t color;

    if (lines->side == 0 && ray->rayDirX > 0)
        texture = game->textures.east;
    else if (lines->side == 0 && ray->rayDirX < 0)
        texture = game->textures.west;
    else if (lines->side == 1 && ray->rayDirY > 0)
        texture = game->textures.south;
    else
        texture = game->textures.north;

    if (lines->side == 0)
        wallX = game->posY + ray->perpWallDist * ray->rayDirY;
    else
        wallX = game->posX + ray->perpWallDist * ray->rayDirX;
    wallX -= floor(wallX);

    texX = (int)(wallX * (double)texture->width);
    if ((lines->side == 0 && ray->rayDirX > 0) || (lines->side == 1 && ray->rayDirY < 0))
        texX = texture->width - texX - 1;

    for (y = lines->drawStart; y < lines->drawEnd; y++) {
        int d = y * 256 - SCREENHEIGHT * 128 + lines->lineHeight * 128;
        texY = ((d * texture->height) / lines->lineHeight) / 256;
        uint8_t *pixel = texture->pixels + (texY * texture->width + texX) * 4;
        color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
        mlx_put_pixel(game->image, x, y, color);
    }
}

void ray_y(t_game game, t_ray *ray)
{
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (game.posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - game.posY) * ray->deltaDistY;
    }
}

void	dda_function(t_ray *ray, t_game *game, int *hit, int *side)
{
	while (*hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			*side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			*side = 1;
		}
		if (game->worldMap[ray->mapY][ray->mapX] > '0')
			*hit = 1;
	}
	if (*side == 0)
		ray->perpWallDist = (ray->mapX - game->posX + (1 - ray->stepX) / 2)
			/ ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - game->posY + (1 - ray->stepY) / 2)
			/ ray->rayDirY;
}

void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->cameraX = 2 * x / (double)SCREENWIDTH - 1;
	ray->rayDirX = game->dirX + game->planeX * ray->cameraX;
	ray->rayDirY = game->dirY + game->planeY * ray->cameraX;
	ray->mapX = (int)game->posX;
	ray->mapY = (int)game->posY;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - game->posX) * ray->deltaDistX;
	}
    ray_y(*game, ray);
}

void draw_floor_and_ceiling(t_game *game, int x, int drawEnd, int drawStart)
{
    draw_line(game, x, drawEnd + 1, SCREENHEIGHT, 0xAAAAAAFF); // Color gris claro
    draw_line(game, x, 0, drawStart, 0x87CEEBFF); // Color azul claro para el cielo
}


void update_and_render(void *param)
{
    t_lines lines;
    t_game *game;
    t_ray ray;

    lines.x = 0;
    game = (t_game *)param;
    clear_image(game->image, 0x000000FF); // Limpiar pantalla

    // Dibujar el cielo y el suelo en color sólido
    for (int x = 0; x < SCREENWIDTH; x++) {
        draw_line(game, x, 0, SCREENHEIGHT / 2, 0x87CEEBFF); // Color azul claro para el cielo
        draw_line(game, x, SCREENHEIGHT / 2, SCREENHEIGHT, 0x228B22FF); // Color verde para el suelo
    }

    while (lines.x < SCREENWIDTH)
    {
        init_ray(&ray, game, lines.x);
        lines.hit = 0;
        dda_function(&ray, game, &lines.hit, &lines.side);
        lines.lineHeight = (int)(SCREENHEIGHT / ray.perpWallDist);
        lines.drawStart = -lines.lineHeight / 2 + SCREENHEIGHT / 2;
        if (lines.drawStart < 0)
            lines.drawStart = 0;
        lines.drawEnd = lines.lineHeight / 2 + SCREENHEIGHT / 2;
        if (lines.drawEnd >= SCREENHEIGHT)
            lines.drawEnd = SCREENHEIGHT - 1;

        // Dibujar la pared con textura
        draw_wall_with_texture(game, &ray, lines.x, &lines);
        lines.x++;
    }
    mlx_image_to_window(game->mlx, game->image, 0, 0);
}
