#include "cub3d.h"


// Prueba par a sacar una imagen en pantalla con la mlx42

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Function to handle key events
void key_hook(mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window((mlx_t *)param);
    }
}

int main(void)
{
    mlx_t *mlx;
    mlx_image_t *image;
    mlx_texture_t *texture;

    // Initialize MLX42
    mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Texture Example", true);
    if (!mlx)
    {
        fprintf(stderr, "Failed to initialize MLX42.\n");
        return EXIT_FAILURE;
    }

    // Load texture
    texture = mlx_load_png("texture.png"); // Replace with your texture file path
    if (!texture)
    {
        fprintf(stderr, "Failed to load texture.\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Create an image from the texture
    image = mlx_texture_to_image(mlx, texture);
    if (!image)
    {
        fprintf(stderr, "Failed to create image from texture.\n");
        mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Add the image to the window
    if (mlx_image_to_window(mlx, image, 0, 0) < 0)
    {
        fprintf(stderr, "Failed to display image in window.\n");
        mlx_delete_texture(texture);
        mlx_delete_image(mlx, image);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Set key hook to close window with ESC
    mlx_key_hook(mlx, key_hook, mlx);

    // Main loop
    mlx_loop(mlx);

    // Cleanup
    mlx_delete_texture(texture);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
