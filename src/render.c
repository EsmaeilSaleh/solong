#include "so_long.h"

#define TEX_WALL "textures/wall.xpm"
#define TEX_FLOOR "textures/floor.xpm"
#define TEX_PLAYER "textures/player.xpm"
#define TEX_EXIT "textures/exit.xpm"
#define TEX_COLLECT "textures/collect.xpm"

static void	load_image(t_game *game, t_img *img, const char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, (char *)path, &img->w, &img->h);
	if (!img->img)
		error_exit("Failed to load texture", game);
}

static void draw_moves(t_game *game)
{
	char	*num;
	char	*label;

	num = ft_itoa(game->moves);
	if(!num)
		return ;
	label = ft_strjoin("Moves: ", num);
	free(num);
	if (!label)
		return ;
	mlx_string_put(game->mlx, game->win, 10, 20, 0xffffff, label);
	free(label);
}

void	load_textures(t_game *game)
{
	load_image(game, &game->wall, TEX_WALL);
	load_image(game, &game->floor, TEX_FLOOR);
	load_image(game, &game->player, TEX_PLAYER);
	load_image(game, &game->exit, TEX_EXIT);
	load_image(game, &game->collect, TEX_COLLECT);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->floor.img, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					game->wall.img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->collect.img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win,
					game->exit.img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->player.img, game->player_x * TILE_SIZE,
		game->player_y * TILE_SIZE);
	draw_moves(game);
}
