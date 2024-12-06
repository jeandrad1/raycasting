#include "raycasting.h"

#define WIDTH 640
#define HEIGHT 640
#define TILE_SIZE 64
#define MOVE_SPEED 5 // Velocidad del círculo en píxeles
#define CIRCLE_SIZE 48 // Tamaño del círculo (48x48)

// Estructura del juego
typedef struct {
    mlx_t* mlx;
    mlx_image_t* img;
    mlx_image_t* circle_img;
    float x;
    float y;
    int map[10][10];
} game_t;

// Función para dibujar un cuadrado en la imagen
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

// Función para dibujar el mapa
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

// Función para verificar las colisiones del círculo con el mapa
int is_valid_move(game_t* game, float new_x, float new_y)
{
    // Coordenadas del área del círculo en la ventana
    int start_x = (int)new_x;
    int start_y = (int)new_y;

    // Recorrer los píxeles del círculo como un rectángulo
    for (int i = 0; i < CIRCLE_SIZE; i++)
    {
        for (int j = 0; j < CIRCLE_SIZE; j++)
        {
            // Calcular la posición global del píxel en el mapa
            int global_x = start_x + j;
            int global_y = start_y + i;

            // Calcular las coordenadas del mapa correspondientes
            int map_x = global_x / TILE_SIZE;
            int map_y = global_y / TILE_SIZE;

            // Verificar colisión con los límites o una pared
            if (map_x < 0 || map_y < 0 || map_x >= 10 || map_y >= 10 || game->map[map_y][map_x] == 1)
                return 0; // Movimiento no válido
        }
    }

    return 1; // Movimiento válido
}

// Función para manejar las teclas presionadas
void key_hook(mlx_key_data_t keydata, void* param)
{
    game_t* game = (game_t*)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        float new_x = game->x;
        float new_y = game->y;

        // Movimiento basado en las teclas
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
            game->x = new_x;
            game->y = new_y;
        }

        // Redibujar el mapa
        mlx_image_to_window(game->mlx, game->img, 0, 0);
        draw_map(game->img, game->map, 10, 10);

        // Redibujar la textura del círculo
        mlx_image_to_window(game->mlx, game->circle_img, (int)game->x, (int)game->y);
    }
}

int main(void)
{
    // Mapa con pasillos más anchos y estrechos
    int map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Inicialización de MLX
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

    // Cargar y crear la imagen del círculo
    mlx_texture_t* texture = mlx_load_png("textures/circulo.png");
    if (!texture)
    {
        mlx_delete_image(mlx, img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Crear y redimensionar la imagen del círculo
    mlx_image_t* circle_img = mlx_texture_to_image(mlx, texture);
    if (!circle_img)
    {
        mlx_delete_image(mlx, img);
        mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    mlx_resize_image(circle_img, CIRCLE_SIZE, CIRCLE_SIZE);

    // Inicializar el círculo en la posición (1, 1)
    game_t game = {mlx, img, circle_img, 1 * TILE_SIZE, 1 * TILE_SIZE, {0}};
    memcpy(game.map, map, sizeof(map));

    mlx_image_to_window(mlx, circle_img, (int)game.x, (int)game.y);

    mlx_key_hook(mlx, key_hook, &game);

    mlx_loop(mlx);

    mlx_delete_image(mlx, img);
    mlx_delete_image(mlx, circle_img);
    mlx_delete_texture(texture);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
