/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:30 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 18:24:36 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_y(t_game game, t_ray *ray)
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

void	draw_floor_and_ceiling(t_game *game, int x)
{
	draw_line(game, x, 0, SCREENHEIGHT / 2, 0x87CEEBFF);
	draw_line(game, x, SCREENHEIGHT / 2, SCREENHEIGHT, 0x228B22FF);
}

void	update_and_render(void *param)
{
	t_lines	lines;
	t_game	*game;
	t_ray	ray;

	lines.x = 0;
	game = (t_game *)param;
	clear_image(game->image, 0x000000FF);
	while (lines.x < SCREENWIDTH)
	{
		draw_floor_and_ceiling(game, lines.x);
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
		draw_wall_with_texture(game, &ray, lines.x, &lines);
		lines.x++;
	}
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}
