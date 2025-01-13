/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:30:26 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/13 18:30:33 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(const char *message, t_game *game)
{
	fprintf(stderr, "Error: %s\n", message);
	free_map(game->worldMap, game->mapHeight);
	exit(1);
}

void	load_walls(t_game *game)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42("textures/bluestone.xpm42");
	if (!xpm)
		error("texture not found", game);
	game->textures.north = &xpm->texture;
	xpm = mlx_load_xpm42("textures/eagle.xpm42");
	if (!xpm)
		error("texture not found", game);
	game->textures.south = &xpm->texture;
	xpm = mlx_load_xpm42("textures/mossy.xpm42");
	if (!xpm)
		error("texture not found", game);
	game->textures.west = &xpm->texture;
	xpm = mlx_load_xpm42("textures/redbrick.xpm42");
	if (!xpm)
		error("texture not found", game);
	game->textures.east = &xpm->texture;
}
