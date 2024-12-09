/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/09 13:57:54 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main() {
    t_game game;

    int worldMap[MAPWIDTH][MAPHEIGHT] =
    {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 3, 0, 1, 0, 3, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 3, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    memcpy(game.worldMap, worldMap, sizeof(worldMap));

    game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3d", false);  // Inicializa MLX42
    game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);

    game.posX = 5.0;
    game.posY = 5.0;
    game.dirX = -1.0;
    game.dirY = 0.0;
    game.planeX = 0.0;
    game.planeY = 0.66;

    mlx_loop_hook(game.mlx, update_and_render, &game); // Actualiza el renderizado
    mlx_key_hook(game.mlx, move_player, &game); // Maneja la entrada del teclado

    mlx_loop(game.mlx); // Inicia el bucle del evento
    
    return 0;
}
