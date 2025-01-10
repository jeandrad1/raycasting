#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03
#define PLAYER_RADIUS 0.2 // Radius for collision detection

typedef struct s_game {
    mlx_t *mlx;
    mlx_image_t *image;
    mlx_texture_t *northTexture;
    mlx_texture_t *southTexture;
    mlx_texture_t *eastTexture;
    mlx_texture_t *westTexture;
    char **worldMap;
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
    int mapHeight, mapWidth;
} t_game;

typedef struct s_ray {
    double cameraX, rayDirX, rayDirY;
    int mapX, mapY;
    double sideDistX, sideDistY;
    double deltaDistX, deltaDistY;
    double perpWallDist;
    int stepX, stepY;
} t_ray;

typedef struct s_lines {
    int lineHeight;
    int drawStart, drawEnd;
    int side, hit;
} t_lines;

// Function to check collision with walls considering PLAYER_RADIUS
int is_collision(t_game *game, double x, double y) {
    return game->worldMap[(int)(y)][(int)(x)] != '0' || // Center point
           game->worldMap[(int)(y + PLAYER_RADIUS)][(int)(x)] != '0' || // Top edge
           game->worldMap[(int)(y - PLAYER_RADIUS)][(int)(x)] != '0' || // Bottom edge
           game->worldMap[(int)(y)][(int)(x + PLAYER_RADIUS)] != '0' || // Right edge
           game->worldMap[(int)(y)][(int)(x - PLAYER_RADIUS)] != '0';   // Left edge
}

// Function to load textures
void load_textures(t_game *game) {
    game->northTexture = mlx_load_png("north.png");
    game->southTexture = mlx_load_png("south.png");
    game->eastTexture = mlx_load_png("east.png");
    game->westTexture = mlx_load_png("west.png");
    if (!game->northTexture || !game->southTexture || !game->eastTexture || !game->westTexture) {
        fprintf(stderr, "Error loading textures.\n");
        exit(EXIT_FAILURE);
    }
}

// Function to free textures
void free_textures(t_game *game) {
    mlx_delete_texture(game->northTexture);
    mlx_delete_texture(game->southTexture);
    mlx_delete_texture(game->eastTexture);
    mlx_delete_texture(game->westTexture);
}

// Function to initialize the ray
void init_ray(t_ray *ray, t_game *game, int x) {
    ray->cameraX = 2 * x / (double)SCREENWIDTH - 1;
    ray->rayDirX = game->dirX + game->planeX * ray->cameraX;
    ray->rayDirY = game->dirY + game->planeY * ray->cameraX;
    ray->mapX = (int)game->posX;
    ray->mapY = (int)game->posY;
    ray->deltaDistX = fabs(1 / ray->rayDirX);
    ray->deltaDistY = fabs(1 / ray->rayDirY);

    if (ray->rayDirX < 0) {
        ray->stepX = -1;
        ray->sideDistX = (game->posX - ray->mapX) * ray->deltaDistX;
    } else {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - game->posX) * ray->deltaDistX;
    }

    if (ray->rayDirY < 0) {
        ray->stepY = -1;
        ray->sideDistY = (game->posY - ray->mapY) * ray->deltaDistY;
    } else {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - game->posY) * ray->deltaDistY;
    }
}

// Function to implement DDA algorithm
void dda_function(t_ray *ray, t_game *game, int *hit, int *side) {
    while (*hit == 0) {
        if (ray->sideDistX < ray->sideDistY) {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            *side = 0;
        } else {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            *side = 1;
        }
        if (game->worldMap[ray->mapY][ray->mapX] > '0')
            *hit = 1;
    }

    if (*side == 0)
        ray->perpWallDist = (ray->mapX - game->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        ray->perpWallDist = (ray->mapY - game->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
}

// Function to draw walls with textures
void draw_wall_with_texture(t_game *game, t_ray *ray, int x, t_lines *lines) {
    mlx_texture_t *texture;
    double wallX;
    int texX, texY;
    int y;
    uint32_t color;

    if (lines->side == 0 && ray->rayDirX > 0)
        texture = game->eastTexture;
    else if (lines->side == 0 && ray->rayDirX < 0)
        texture = game->westTexture;
    else if (lines->side == 1 && ray->rayDirY > 0)
        texture = game->southTexture;
    else
        texture = game->northTexture;

    if (lines->side == 0)
        wallX = game->posY + ray->perpWallDist * ray->rayDirY;
    else
        wallX = game->posX + ray->perpWallDist * ray->rayDirX;
    wallX -= floor(wallX);

    texX = (int)(wallX * (double)texture->width);
    if ((lines->side == 0 && ray->rayDirX < 0) || (lines->side == 1 && ray->rayDirY > 0))
        texX = texture->width - texX - 1;

    for (y = lines->drawStart; y < lines->drawEnd; y++) {
        int d = y * 256 - SCREENHEIGHT * 128 + lines->lineHeight * 128;
        texY = ((d * texture->height) / lines->lineHeight) / 256;
        color = *(uint32_t *)(texture->pixels + (texY * texture->width + texX) * 4);
        mlx_put_pixel(game->image, x, y, color);
    }
}

// Function to update and render the scene
void update_and_render(void *param) {
    t_game *game = (t_game *)param;
    t_ray ray;
    t_lines lines;

    lines.x = 0;
    mlx_clear_image(game->image, 0x000000FF);
    while (lines.x < SCREENWIDTH) {
        init_ray(&ray, game, lines.x);
        lines.hit = 0;
        dda_function(&ray, game, &lines.hit, &lines.side);
        lines.lineHeight = (int)(SCREENHEIGHT / ray.perpWallDist);
        lines.drawStart = -lines.lineHeight / 2 + SCREENHEIGHT / 2;
        if (lines.drawStart < 0) lines.drawStart = 0;
        lines.drawEnd = lines.lineHeight / 2 + SCREENHEIGHT / 2;
        if (lines.drawEnd >= SCREENHEIGHT) lines.drawEnd = SCREENHEIGHT - 1;
        draw_wall_with_texture(game, &ray, lines.x, &lines);
        lines.x++;
    }
    mlx_image_to_window(game->mlx, game->image, 0, 0);
}

// Function to handle player movement
void move_player(t_game *game, double moveX, double moveY) {
    if (!is_collision(game, game->posX + moveX, game->posY))
        game->posX += moveX;
    if (!is_collision(game, game->posX, game->posY + moveY))
        game->posY += moveY;
}

// Function to handle input
void key_hook(mlx_key_data_t keydata, void *param) {
    t_game *game = (t_game *)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(game->mlx);

    double moveSpeed = MOVE_SPEED;
    double rotSpeed = ROT_SPEED;

    if (keydata.key == MLX_KEY_W)
        move_player(game, game->dirX * moveSpeed, game->dirY * moveSpeed);
    if (keydata.key == MLX_KEY_S)
        move_player(game, -game->dirX * moveSpeed, -game->dirY * moveSpeed);
    if (keydata.key == MLX_KEY_A)
        move_player(game, -game->planeX * moveSpeed, -game->planeY * moveSpeed);
    if (keydata.key == MLX_KEY_D)
        move_player(game, game->planeX * moveSpeed, game->planeY * moveSpeed);
    if (keydata.key == MLX_KEY_RIGHT) {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
        game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
        game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
    }
    if (keydata.key == MLX_KEY_LEFT) {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
        game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
        game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
    }
}

int main(void) {
    t_game game;

    // Initialize MLX42
    game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Doom-Like with Collisions", true);
    if (!game.mlx) return EXIT_FAILURE;

    // Load textures
    game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
    load_textures(&game);

    // Initialize player and map
    game.posX = 22; game.posY = 12;
    game.dirX = -1; game.dirY = 0;
    game.planeX = 0; game.planeY = 0.66;
    game.worldMap = /* Initialize your map here */;

    // Set hooks and main loop
    mlx_key_hook(game.mlx, key_hook, &game);
    mlx_loop_hook(game.mlx, update_and_render, &game);
    mlx_loop(game.mlx);

    // Cleanup
    free_textures(&game);
    mlx_terminate(game.mlx);
    return EXIT_SUCCESS;
}
