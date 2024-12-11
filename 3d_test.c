/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:10:38 by jeandrad          #+#    #+#             */
/*   Updated: 2024/12/11 19:27:51 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MAPWIDTH 10
#define MAPHEIGHT 10

typedef struct {
    mlx_t *mlx;
    mlx_image_t *image;
    double posX, posY;    // Posición del jugador
    double dirX, dirY;    // Dirección de la cámara
    double planeX, planeY; // Plano de la cámara (para la perspectiva)
} t_game;

// Mapa del mundo (0 = vacío, 1 = paredes)
int worldMap[MAPWIDTH][MAPHEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Función para limpiar la imagen
void clear_image(mlx_image_t *image, uint32_t color) {
    for (int y = 0; y < SCREENHEIGHT; y++) {
        for (int x = 0; x < SCREENWIDTH; x++) {
            mlx_put_pixel(image, x, y, color);
        }
    }
}

// Función para dibujar una línea vertical (de una pared)
void draw_line(t_game *game, int x, int start, int end, uint32_t color) {
    for (int y = start; y < end; y++) {
        mlx_put_pixel(game->image, x, y, color);
    }
}

// Función para actualizar y renderizar la imagen
void update_and_render(void *param) {
    t_game *game = (t_game *)param;
    clear_image(game->image, 0x000000FF); // Limpiar pantalla

    for (int x = 0; x < SCREENWIDTH; x++) {
        // Calculamos la dirección del rayo
        double cameraX = 2 * x / (double)SCREENWIDTH - 1; // Mapeo de la pantalla en [-1, 1]
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        // Posición inicial del rayo
        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

        // Longitudes del rayo
        double sideDistX, sideDistY;

        // Dirección de los pasos en cada eje
        int stepX, stepY;

        // Variables de distancia
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        // Determinar el paso en cada eje
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (game->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
        }

        // Realizar el "DDA" (Digital Differential Analyzer) para encontrar la intersección del rayo con las paredes
        int hit = 0;
        while (hit == 0) {
            // Si el rayo golpea una pared en el eje X
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                if (worldMap[mapX][mapY] > 0) hit = 1;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }
        }

        // Calcular la distancia hasta el punto de intersección del rayo
        if (sideDistX < sideDistY) {
            perpWallDist = (mapX - game->povoid update_and_render(void *param)
sX + (1 - stepX) / 2) / rayDirX;
        } else {
            perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;
        }

        // Calcular la altura de la pared
        int lineHeight = (int)(SCREENHEIGHT / perpWallDist);

        // Calcular el inicio y final de la pared en la pantalla
        int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawEnd >= SCREENHEIGHT) drawEnd = SCREENHEIGHT - 1;

        // Determinar el color de la pared
        uint32_t color;
        switch (worldMap[mapX][mapY])void update_and_render(void *param)

        {
            case 1: color = 0xFF0000; break; // Paredes rojas
            case 2: color = 0x00FF00; break; // Paredes verdes
            case 3: color = 0x0000FF; break; // Paredes azules
            default: color = 0xFFFFFF; break;  // Blanco
        }

        // Dibujar la pared
        draw_line(game, x, drawStart, drawEnd, color);
    }
    mlx_image_to_window(game->mlx, game->image, 0, 0); // Mostrar la imagen en la ventana
}

// Función para manejar las teclas (MLX42 no tiene función directa para esto, se maneja de otra forma)
void move_player(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    double moveSpeed = 0.1;
    double rotSpeed = 0.05;


    if (keydata.key == MLX_KEY_ESCAPE)
    {
        mlx_close_window(game->mlx);
        exit(0);
    }
    if (keydata.key == MLX_KEY_W)
    {
        if (!worldMap[(int)(game->posX + game->dirX * moveSpeed)][(int)(game->posY)]) game->posX += game->dirX * moveSpeed;
        if (!worldMap[(int)(game->posX)][(int)(game->posY + game->dirY * moveSpeed)]) game->posY += game->dirY * moveSpeed;
    }
    if (keydata.key == MLX_KEY_S)
    {#include ""
        if (!worldMap[(int)(game->posX - game->dirX * moveSpeed)][(int)(game->posY)]) game->posX -= game->dirX * moveSpeed;
        if (!worldMap[(int)(game->posX)][(int)(game->posY - game->dirY * moveSpeed)]) game->posY -= game->dirY * moveSpeed;
    }
    if (keydata.key == MLX_KEY_A)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
        game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
        game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
    }
    if (keydata.key == MLX_KEY_D)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
        game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
        game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
    }
}

// Función principal
int main() {
    t_game game;

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
