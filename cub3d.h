#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <stdio.h>
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
# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

typedef struct {
    mlx_t *mlx;
    mlx_image_t *image;
    double posX, posY;    // Posición del jugador
    double dirX, dirY;    // Dirección de la cámara
    double planeX, planeY; // Plano de la cámara (para la perspectiva)
    int worldMap[MAPWIDTH][MAPHEIGHT];
} t_game;

//funciones
void clear_image(mlx_image_t *image, uint32_t color);
void draw_line(t_game *game, int x, int start, int end, uint32_t color);
void move_player(mlx_key_data_t keydata, void *param);
void update_and_render(void *param);



#endif