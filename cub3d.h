#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"


// Todo esto deberia ir en una structura con valores fijos
# define MAPWIDTH 10
# define MAPHEIGHT 10
# define SCREENWIDTH 1920
# define SCREENHEIGHT 1280
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.03

typedef struct
{
    mlx_t *mlx;
    mlx_image_t *image;
    double posX, posY;    // Posición del jugador
    double dirX, dirY;    // Dirección de la cámara
    double planeX, planeY; // Plano de la cámara (para la perspectiva)
    char **worldMap;      // Mapa del mundo
    int mapWidth;
    int mapHeight;
} t_game;

typedef struct
{
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    int stepX;
    int stepY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
} t_ray;

typedef struct lines
{
    int     x;   
    int     hit;
    int     side;   
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	uint32_t color;
} t_lines;

//funciones
void clear_image(mlx_image_t *image, uint32_t color);
void draw_line(t_game *game, int x, int start, int end, uint32_t color);
void move_player(mlx_key_data_t keydata, void *param);
void update_and_render(void *param);
char **initialize_map(const char *mapData[], int mapHeight);
void free_map(char **map, int mapHeight);



#endif