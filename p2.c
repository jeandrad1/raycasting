void foward_and_back_mov(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    double moveSpeed = MOVE_SPEED;
    if (keydata.key == MLX_KEY_W)
    {
        // Verificación para movimiento hacia adelante
        if (game->worldMap[(int)(game->player_pos_y + game->player_dir_y * moveSpeed)][(int)(game->player_pos_x)] == '0')
            game->player_pos_y += game->player_dir_y * moveSpeed;
        if (game->worldMap[(int)(game->player_pos_y)][(int)(game->player_pos_x + game->player_dir_x * moveSpeed)] == '0')
            game->player_pos_x += game->player_dir_x * moveSpeed;
    }
    if (keydata.key == MLX_KEY_S)
    {
        // Verificación para movimiento hacia atrás
        if (game->worldMap[(int)(game->player_pos_y - game->player_dir_y * moveSpeed)][(int)(game->player_pos_x)] == '0')
            game->player_pos_y -= game->player_dir_y * moveSpeed;
        if (game->worldMap[(int)(game->player_pos_y)][(int)(game->player_pos_x - game->player_dir_x * moveSpeed)] == '0')
            game->player_pos_x -= game->player_dir_x * moveSpeed;
    }
}


