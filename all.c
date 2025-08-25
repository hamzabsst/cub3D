

// FIX 3: Add bounds checking to perform_dda
static int perform_dda(t_game *game, t_ray *data)
{
    int side;
    int hit;

    hit = 0;
    while (hit == 0)
    {
        if (data->side_dist_x < data->side_dist_y)
        {
            data->side_dist_x += data->delta_dist_x;
            data->player_x += data->step_x;
            side = 0;
        }
        else
        {
            data->side_dist_y += data->delta_dist_y;
            data->player_y += data->step_y;
            side = 1;
        }

        // FIX: Add bounds checking to prevent seeing through map edges
        if (data->player_x < 0 || data->player_x >= MAP_WIDTH ||
            data->player_y < 0 || data->player_y >= MAP_HEIGHT)
        {
            hit = 1; // Hit map boundary
            break;
        }

        if (game->map[data->player_y][data->player_x] == '1' ||
            game->map[data->player_y][data->player_x] == ' ')
            hit = 1;
    }
    return (side);
}

// FIX 4: Improve cast_ray with better distance handling
static t_hit cast_ray(t_game *game, double ray_x, double ray_y)
{
    t_hit result;
    t_ray data;
    int side;

    init_params(game, ray_x, ray_y, &data);
    side = perform_dda(game, &data);

    // Calculate distance with bounds checking
    if (side == 0)
        result.distance = (data.player_x - game->player_x + (1 - data.step_x) / 2) / ray_x;
    else
        result.distance = (data.player_y - game->player_y + (1 - data.step_y) / 2) / ray_y;

    // FIX: Ensure distance is never negative or too small
    if (result.distance <= 0.001)
        result.distance = 0.001;

    result.is_vertical = side;
    set_texture(game, &result, &data, side);

    // Calculate hit point
    if (side == 0)
        result.hit_point = game->player_y + result.distance * ray_y;
    else
        result.hit_point = game->player_x + result.distance * ray_x;

    // FIX: Better hit point normalization
    result.hit_point = result.hit_point - floor(result.hit_point);
    if (result.hit_point < 0)
        result.hit_point += 1.0;
    if (result.hit_point >= 1.0)
        result.hit_point -= 1.0;

    return (result);
}

// FIX 5: Add initialization check for init_params
static void init_params(t_game *game, double ray_x, double ray_y, t_ray *data)
{
    data->player_x = (int)game->player_x;
    data->player_y = (int)game->player_y;

    // FIX: Prevent division by zero
    if (fabs(ray_x) < 0.0001)
        ray_x = (ray_x >= 0) ? 0.0001 : -0.0001;
    if (fabs(ray_y) < 0.0001)
        ray_y = (ray_y >= 0) ? 0.0001 : -0.0001;

    data->delta_dist_x = fabs(1 / ray_x);
    data->delta_dist_y = fabs(1 / ray_y);

    if (ray_x < 0)
    {
        data->step_x = -1;
        data->side_dist_x = (game->player_x - data->player_x) * data->delta_dist_x;
    }
    else
    {
        data->step_x = 1;
        data->side_dist_x = (data->player_x + 1.0 - game->player_x) * data->delta_dist_x;
    }
    if (ray_y < 0)
    {
        data->step_y = -1;
        data->side_dist_y = (game->player_y - data->player_y) * data->delta_dist_y;
    }
    else
    {
        data->step_y = 1;
        data->side_dist_y = (data->player_y + 1.0 - game->player_y) * data->delta_dist_y;
    }
}

// FIX 6: Improve set_texture to handle edge cases
static void set_texture(t_game *game, t_hit *result, t_ray *data, int side)
{
    // FIX: Add bounds checking for map access
    if (data->player_y < 0 || data->player_y >= MAP_HEIGHT ||
        data->player_x < 0 || data->player_x >= MAP_WIDTH)
    {
        result->texture = &game->no_texture;
        return;
    }

    if (game->map[data->player_y][data->player_x] == ' ')
        result->texture = &game->no_texture;
    else
    {
        if (side == 0) // Vertical wall
        {
            if (data->step_x > 0)
                result->texture = &game->ea_texture; // East wall
            else
                result->texture = &game->we_texture; // West wall
        }
        else // Horizontal wall
        {
            if (data->step_y > 0)
                result->texture = &game->so_texture; // South wall
            else
                result->texture = &game->no_texture; // North wall (or use north texture if you have one)
        }
    }
}

// OPTIONAL: Add this function to clear specific wall columns if needed
void clear_wall_column(t_game *game, int screen_x)
{
    int y;
    char *row_addr;
    int *pixel;

    if (screen_x < 0 || screen_x >= WIN_WIDTH)
        return;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        row_addr = game->buffer.addr + (y * game->buffer.line_length);
        pixel = (int *)(row_addr + screen_x * (game->buffer.bits_per_pixel / 8));

        if (y < WIN_HEIGHT / 2)
            *pixel = game->c_rgb;  // Sky color
        else
            *pixel = game->f_rgb;  // Floor color
        y++;
    }
}
