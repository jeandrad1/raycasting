#include "raycasting.h"

#define WIDTH 640
#define HEIGHT 640
#define TILE_SIZE 64
#define MOVE_SPEED 5 // Velocidad del círculo en píxeles

typedef struct {
    mlx_t* mlx;
    mlx_image_t* img;
    mlx_image_t* circle_img;
    float x;
    float y;
    int map[10][10];
} game_t;

void draw_square(mlx_image_t* img, int x, int y, int size, uint32_t color)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            mlx_put_pixel(img, x + i, y + j, color);
        }
    }
}

void draw_map(mlx_image_t* img, int map[][10], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (map[i][j] == 1)
                draw_square(img, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0x0000FFFF); // Azul
            else
                draw_square(img, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0xFFFFFFFF); // Blanco
        }
    }
}

int is_valid_move(game_t* game, float new_x, float new_y)
{
    // Calcular las esquinas del círculo
    int left = (int)(new_x / TILE_SIZE);
    int right = (int)((new_x + TILE_SIZE - 1) / TILE_SIZE);
    int top = (int)(new_y / TILE_SIZE);
    int bottom = (int)((new_y + TILE_SIZE - 1) / TILE_SIZE);

    // Verificar colisiones con el mapa
    if (left < 0 || right >= 10 || top < 0 || bottom >= 10)
        return 0;

    if (game->map[top][left] == 1 || game->map[top][right] == 1 ||
        game->map[bottom][left] == 1 || game->map[bottom][right] == 1)
        return 0;

    return 1;
}

void key_hook(mlx_key_data_t keydata, void* param)
{
    game_t* game = (game_t*)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        float new_x = game->x;
        float new_y = game->y;

        if (keydata.key == MLX_KEY_W)
            new_y -= MOVE_SPEED;
        else if (keydata.key == MLX_KEY_S)
            new_y += MOVE_SPEED;
        else if (keydata.key == MLX_KEY_A)
            new_x -= MOVE_SPEED;
        else if (keydata.key == MLX_KEY_D)
            new_x += MOVE_SPEED;
        else if (keydata.key == MLX_KEY_ESCAPE)
        {
            mlx_terminate(game->mlx);
            exit(0);
        }

        // Verificar si el movimiento es válido antes de actualizar las coordenadas
        if (is_valid_move(game, new_x, new_y))
        {
            // Borrar el círculo anterior redibujando el mapa
            draw_map(game->img, game->map, 10, 10);
            mlx_image_to_window(game->mlx, game->img, 0, 0);

            game->x = new_x;
            game->y = new_y;

            // Redibujar el círculo en la nueva posición
            mlx_image_to_window(game->mlx, game->circle_img, (int)game->x, (int)game->y);
        }
    }
}

int main(void)
{
int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
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

    // Inicializar el círculo en la posición (1, 1), asegurándonos de que sea una celda válida
    game_t game = {mlx, img, circle_img, TILE_SIZE, TILE_SIZE, {0}};
    memcpy(game.map, map, sizeof(map));

    if (!is_valid_move(&game, game.x, game.y))
    {
        fprintf(stderr, "Error: posición inicial no válida\n");
        mlx_delete_image(mlx, img);
        mlx_delete_image(mlx, circle_img);
        mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    mlx_image_to_window(mlx, circle_img, (int)game.x, (int)game.y);

    mlx_key_hook(mlx, key_hook, &game);

    mlx_loop(mlx);

    mlx_delete_image(mlx, img);
    mlx_delete_image(mlx, circle_img);
    mlx_delete_texture(texture);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
