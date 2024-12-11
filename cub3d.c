/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/11 19:28:33 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(char **map, int mapHeight)
{
    for (int i = 0; i < mapHeight; i++)
        free(map[i]);
    free(map);
}

char **initialize_map(const char *mapData[], int mapHeight)
{
    char **map = malloc(mapHeight * sizeof(char *));
    if (!map)
        return NULL;

    for (int i = 0; i < mapHeight; i++) {
        map[i] = strdup(mapData[i]);
        if (!map[i]) {
            free_map(map, i);
            return NULL;
        }
    }
    return map;
}


int main()
{
    t_game game;

    // Datos iniciales del mapa
    const char *mapData[] =
    {
        "111111",
        "100001",
        "100001",
        "100001",
        "111111"
    };
    int mapHeight = sizeof(mapData) / sizeof(mapData[0]);
    int mapWidth = strlen(mapData[0]);

    game.mapHeight = mapHeight;
    game.mapWidth = mapWidth;
    game.worldMap = initialize_map(mapData, mapHeight);
    if (!game.worldMap) {
        fprintf(stderr, "Error: no se pudo inicializar el mapa.\n");
        return 1;
    }

    game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Cub3D", true);
    if (!game.mlx) {
        fprintf(stderr, "Error: no se pudo inicializar MLX42.\n");
        free_map(game.worldMap, mapHeight);
        return 1;
    }

    game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
    if (!game.image) {
        fprintf(stderr, "Error: no se pudo crear la imagen.\n");
        mlx_terminate(game.mlx);
        free_map(game.worldMap, mapHeight);
        return 1;
    }

    // Posición inicial del jugador
    game.posX = 1.5;
    game.posY = 1.5;
    game.dirX = -1;
    game.dirY = 0;
    game.planeX = 0;
    game.planeY = 0.66;

    mlx_loop_hook(game.mlx, &update_and_render, &game);
    mlx_key_hook(game.mlx, &move_player, &game);

    mlx_loop(game.mlx);

    // Liberar recursos
    free_map(game.worldMap, mapHeight);
    mlx_terminate(game.mlx);
    return 0;
}
