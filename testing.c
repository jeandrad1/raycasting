#include "raycasting.h"

#define WIDTH 800
#define HEIGHT 600
#define TILE_SIZE 50

typedef struct {
    mlx_t* mlx;
    mlx_image_t* img;
    mlx_image_t* circle_img;
    int x;
    int y;
    int map[10][10];
} game_t;

void draw_square(mlx_image_t* img, int x, int y, int size, uint32_t color)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_map(mlx_image_t* img, int map[][10], int rows, int cols)
{
    int i = 0;
    while (i < rows)
    {
        int j = 0;
        while (j < cols)
        {
            if (map[i][j] == 1)
                draw_square(img, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0x0000FFFF); // Azul
            else
                draw_square(img, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0xFFFFFFFF); // Blanco
            j++;
        }
        i++;
    }
}

void key_hook(mlx_key_data_t keydata, void* param)
{
    game_t* game = (game_t*)param;
    int new_x = game->x;
    int new_y = game->y;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_W)
            new_y -= TILE_SIZE;
        else if (keydata.key == MLX_KEY_S)
            new_y += TILE_SIZE;
        else if (keydata.key == MLX_KEY_A)
            new_x -= TILE_SIZE;
        else if (keydata.key == MLX_KEY_D)
            new_x += TILE_SIZE;

        int map_x = new_x / TILE_SIZE;
        int map_y = new_y / TILE_SIZE;

        if (game->map[map_y][map_x] == 0) // Verificación de colisiones
        {
            game->x = new_x;
            game->y = new_y;
        }

        // Redibujar el mapa
        mlx_image_to_window(game->mlx, game->img, 0, 0);
        draw_map(game->img, game->map, 10, 10);

        // Redibujar la textura del círculo
        mlx_image_to_window(game->mlx, game->circle_img, game->x, game->y);
    }
}

int main(void)
{
    int map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Map Example", true);
    if (!mlx)
        return EXIT_FAILURE;

    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
    {
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    draw_map(img, map, 10, 10);

    mlx_image_to_window(mlx, img, 0, 0);

    mlx_texture_t* texture = mlx_load_png("textures/circulo.png");
    if (!texture)
    {
        mlx_delete_image(mlx, img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    mlx_image_t* circle_img = mlx_texture_to_image(mlx, texture);
    if (!circle_img)
    {
        mlx_delete_image(mlx, img);
        mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    mlx_resize_image(circle_img, TILE_SIZE, TILE_SIZE);

    game_t game = {mlx, img, circle_img, WIDTH / 2, HEIGHT / 2,{0}};
    memcpy(game.map, map, sizeof(map));


    mlx_image_to_window(mlx, circle_img, game.x, game.y);

    mlx_key_hook(mlx, key_hook, &game);

    mlx_loop(mlx);

    mlx_delete_image(mlx, img);
    mlx_delete_image(mlx, circle_img);
    mlx_delete_texture(texture);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
