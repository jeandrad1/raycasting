/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/11 18:19:24 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **read_map_from_file(const char *filename, int *mapHeight)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char **map = NULL;
    char *line;
    int height = 0;
    int capacity = 10; // Capacidad inicial para 10 líneas

    map = malloc(capacity * sizeof(char *));
    if (!map)
    {
        perror("Error al asignar memoria");
        close(fd);
        return NULL;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        if (height >= capacity)
        {
            capacity *= 2;
            char **new_map = realloc(map, capacity * sizeof(char *));
            if (!new_map)
            {
                perror("Error al reasignar memoria");
                free(map);
                close(fd);
                return NULL;
            }
            map = new_map;
        }
        map[height++] = line;
    }
    close(fd);
    *mapHeight = height;
    return map;
}

void	free_map(char **map, int mapHeight)
{
	for (int i = 0; i < mapHeight; i++)
		free(map[i]);
	free(map);
}

char	**initialize_map(char **mapData, int mapHeight, t_game *game)
{
    char	**map;

    map = malloc(mapHeight * sizeof(char *));
    if (!map)
        return (NULL);
    for (int i = 0; i < mapHeight; i++)
    {
        map[i] = strdup(mapData[i]);
        if (!map[i])
        {
            free_map(map, i);
            return (NULL);
        }
        for (int j = 0; j < ft_strlen(mapData[i]); j++)
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                game->posX = j + 0.5;
                game->posY = i + 0.5;
                game->initialOrientation = map[i][j];
                map[i][j] = '0'; // Reemplazar la posición inicial con un espacio vacío
            }
        }
    }
    return (map);
}

void set_initial_orientation(t_game *game)
{
    if (game->initialOrientation == 'N')
    {
        game->dirX = 0;
        game->dirY = -1;
        game->planeX = 0.66;
        game->planeY = 0;
    }
    else if (game->initialOrientation == 'S')
    {
        game->dirX = 0;
        game->dirY = 1;
        game->planeX = -0.66;
        game->planeY = 0;
    }
    else if (game->initialOrientation == 'E')
    {
        game->dirX = 1;
        game->dirY = 0;
        game->planeX = 0;
        game->planeY = 0.66;
    }
    else if (game->initialOrientation == 'W')
    {
        game->dirX = -1;
        game->dirY = 0;
        game->planeX = 0;
        game->planeY = -0.66;
    }
}

int	main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <archivo_mapa.ber>\n", argv[0]);
        return (1);
    }

    t_game		game;
    int			mapHeight;
    int			mapWidth;
    char        **mapData;

    // Leer el mapa desde el archivo
    mapData = read_map_from_file(argv[1], &mapHeight);
    if (!mapData)
    {
        fprintf(stderr, "Error: no se pudo leer el mapa del archivo.\n");
        return (1);
    }

    mapWidth = strlen(mapData[0]);
    game.mapHeight = mapHeight;
    game.mapWidth = mapWidth;
    game.worldMap = initialize_map(mapData, mapHeight, &game);
    if (!game.worldMap)
    {
        fprintf(stderr, "Error: no se pudo inicializar el mapa.\n");
        return (1);
    }
	// Inicializar el juego a cero todo 
    game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Cub3D", true);
    if (!game.mlx)
    {
        fprintf(stderr, "Error: no se pudo inicializar MLX42.\n");
        free_map(game.worldMap, mapHeight);
        return (1);
    }
    game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
    if (!game.image)
    {
        fprintf(stderr, "Error: no se pudo crear la imagen.\n");
        mlx_terminate(game.mlx);
        free_map(game.worldMap, mapHeight);
        return (1);
    }

    // Cargar texturas
    load_walls(&game);

    // Establecer la orientación inicial del jugador
    set_initial_orientation(&game);

    mlx_loop_hook(game.mlx, &update_and_render, &game);
    mlx_key_hook(game.mlx, &move_player, &game);
    mlx_loop(game.mlx);
    // Liberar recursos
    free_map(game.worldMap, mapHeight);
    mlx_terminate(game.mlx);
    return (0);
}
