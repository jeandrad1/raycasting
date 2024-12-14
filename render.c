/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:30 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/14 16:00:13 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->posY) * ray->deltaDistY;
	}
}

void	update_and_render(void *param)
{
	int		x;
	int		hit;
	int		side;
	t_game	*game;
		t_ray ray;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
		uint32_t color;

	x = 0;
	game = (t_game *)param;
	clear_image(game->image, 0x000000FF); // Limpiar pantalla
	while (x < SCREENWIDTH)
	{
		init_ray(&ray, game, x);
		hit = 0;
		dda_function(&ray, game, &hit, &side);
		lineHeight = (int)(SCREENHEIGHT / ray.perpWallDist);
		drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
		if (drawEnd >= SCREENHEIGHT)
			drawEnd = SCREENHEIGHT - 1;
		switch (game->worldMap[ray.mapY][ray.mapX])
		{
		case '1':
			color = 0x00FF7FFF;
			break ; // Verde
		case '3':
			color = 0xFF0000FF;
			break ; // Rojo
		default:
			color = 0xFFFFFF;
			break ; // Blanco
		}
		if (side == 1)
			color = color / 2; // Make y-side walls darker
		draw_line(game, x, drawStart, drawEnd, color);
		x++;
	}
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}
