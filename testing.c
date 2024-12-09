#include "raycasting.h"

#define WIDTH 640
#define HEIGHT 640
#define TILE_SIZE 64
#define MOVE_SPEED 5      // Velocidad del círculo en píxeles
#define ROTATE_SPEED 5    // Velocidad de rotación en grados
#define CIRCLE_SIZE 48    // Tamaño del círculo (48x48)
#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)

typedef struct {
    mlx_t* mlx;
    mlx_image_t* img;
    mlx_image_t* circle_img;
    float x;
    float y;
    float angle; // Ángulo de orientación en grados
    int map[10][10];
} game_t;

// Verificar si un píxel está dentro de un muro
int is_pixel_colliding(game_t* game, int px, int py) {
    if (px < 0 || py < 0 || px >= WIDTH || py >= HEIGHT)
        return 1; // Fuera de los límites del mapa

    int map_x = px / TILE_SIZE;
    int map_y = py / TILE_SIZE;

    return game->map[map_y][map_x] == 1; // 1 significa pared
}

// Verificar si el círculo puede moverse a una nueva posición
int is_valid_move(game_t* game, float new_x, float new_y) {
    for (int i = 0; i < CIRCLE_SIZE; i++) {
        for (int j = 0; j < CIRCLE_SIZE; j++) {
            if (is_pixel_colliding(game, new_x + i, new_y + j))
                return 0; // Colisión detectada
        }
    }
    return 1; // Movimiento válido
}

// Dibujar el mapa
void draw_map(mlx_image_t* img, int map[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            uint32_t color = (map[i][j] == 1) ? 0x0000FFFF : 0xFFFFFFFF; // Azul y blanco
            for (int y = 0; y < TILE_SIZE; y++) {
                for (int x = 0; x < TILE_SIZE; x++) {
                    mlx_put_pixel(img, j * TILE_SIZE + x, i * TILE_SIZE + y, color);
                }
            }
        }
    }
}

// Bucle principal del juego
void game_loop(void* param) {
    game_t* game = (game_t*)param;

    float new_x = game->x;
    float new_y = game->y;

    // Movimiento hacia adelante y hacia atrás
    if (mlx_is_key_down(game->mlx, MLX_KEY_W)) {
        new_x += cos(DEG_TO_RAD(game->angle)) * MOVE_SPEED;
        new_y += sin(DEG_TO_RAD(game->angle)) * MOVE_SPEED;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S)) {
        new_x -= cos(DEG_TO_RAD(game->angle)) * MOVE_SPEED;
        new_y -= sin(DEG_TO_RAD(game->angle)) * MOVE_SPEED;
    }

    // Rotación izquierda y derecha
    if (mlx_is_key_down(game->mlx, MLX_KEY_A)) {
        game->angle -= ROTATE_SPEED;
        if (game->angle < 0) game->angle += 360;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D)) {
        game->angle += ROTATE_SPEED;
        if (game->angle >= 360) game->angle -= 360;
    }

    // Validar y aplicar el movimiento
    if (is_valid_move(game, new_x, new_y)) {
        game->x = new_x;
        game->y = new_y;
        game->circle_img->instances[0].x = game->x;
        game->circle_img->instances[0].y = game->y;
    }

    // Salida del juego
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) {
        mlx_terminate(game->mlx);
        exit(0);
    }
}

int main(void) {
    int map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Map Example", true);
    if (!mlx)
        return EXIT_FAILURE;

    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img) {
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    draw_map(img, map, 10, 10);
    mlx_image_to_window(mlx, img, 0, 0);

    mlx_texture_t* texture = mlx_load_png("textures/circulo.png");
    if (!texture) {
        mlx_delete_image(mlx, img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    mlx_image_t* circle_img = mlx_texture_to_image(mlx, texture);
    if (!circle_img) {
        mlx_delete_image(mlx, img);
        mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    mlx_resize_image(circle_img, CIRCLE_SIZE, CIRCLE_SIZE);

    game_t game = {0};
    game.mlx = mlx;
    game.img = img;
    game.circle_img = circle_img;
    game.angle = 0;

    memcpy(game.map, map, sizeof(map));

    // Encontrar una posición inicial válida
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j] == 0) {
                game.x = j * TILE_SIZE;
                game.y = i * TILE_SIZE;
                break;
            }
        }
    }

    mlx_image_to_window(mlx, circle_img, game.x, game.y);
    mlx_loop_hook(mlx, game_loop, &game);
    mlx_loop(mlx);

    mlx_delete_image(mlx, img);
    mlx_delete_image(mlx, circle_img);
    mlx_delete_texture(texture);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
