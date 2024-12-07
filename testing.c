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

// Función para dibujar un cuadrado en la imagen
void draw_square(mlx_image_t* img, int x, int y, int size, uint32_t color) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mlx_put_pixel(img, x + i, y + j, color);
        }
    }
}

// Función para dibujar el mapa
void draw_map(mlx_image_t* img, int map[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 1)
                draw_square(img, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0x0000FFFF); // Azul
            else
                draw_square(img, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0xFFFFFFFF); // Blanco
        }
    }
}

// Función para verificar las colisiones del círculo con el mapa
int is_valid_move(game_t* game, float new_x, float new_y) {
    // Asegúrate de que el círculo no salga del mapa
    if (new_x < 0 || new_y < 0 ||
        new_x + CIRCLE_SIZE > WIDTH ||
        new_y + CIRCLE_SIZE > HEIGHT) {
        return 0; // Movimiento no válido
    }

    int map_x = (int)(new_x + CIRCLE_SIZE / 2) / TILE_SIZE;
    int map_y = (int)(new_y + CIRCLE_SIZE / 2) / TILE_SIZE;

    if (game->map[map_y][map_x] == 1)
        return 0; // Colisión con una pared

    return 1; // Movimiento válido
}

// Función principal del bucle del juego
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
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
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
    game.x = TILE_SIZE;
    game.y = TILE_SIZE;
    game.angle = 0;

    memcpy(game.map, map, sizeof(map));

    mlx_image_to_window(mlx, circle_img, game.x, game.y);
    mlx_loop_hook(mlx, game_loop, &game); // Configuración del loop principal
    mlx_loop(mlx);

    mlx_delete_image(mlx, img);
    mlx_delete_image(mlx, circle_img);
    mlx_delete_texture(texture);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
