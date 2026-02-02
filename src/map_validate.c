#include "so_long.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

static void	check_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->width)
	{
		if (game->map[0][x] != '1' || game->map[game->height - 1][x] != '1')
			error_exit("Map must be surrounded by walls", game);
		x++;
	}
	y = 0;
	while (y < game->height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->width - 1] != '1')
			error_exit("Map must be surrounded by walls", game);
		y++;
	}
}

void	validate_map(t_game *game)
{
	int	x;
	int	y;
	int	count_p;
	int	count_e;
	int	count_c;

	game->height = 0;
	while (game->map[game->height])
		game->height++;
	game->width = (int)ft_strlen(game->map[0]);
	if (game->width <= 0 || game->height <= 0)
		error_exit("Map is empty", game);
	count_p = 0;
	count_e = 0;
	count_c = 0;
	y = 0;
	while (y < game->height)
	{
		if ((int)ft_strlen(game->map[y]) != game->width)
			error_exit("Map must be rectangular", game);
		x = 0;
		while (x < game->width)
		{
			if (!is_valid_char(game->map[y][x]))
				error_exit("Map has invalid characters", game);
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				count_p++;
			}
			else if (game->map[y][x] == 'E')
			{
				game->exit_x = x;
				game->exit_y = y;
				count_e++;
			}
			else if (game->map[y][x] == 'C')
				count_c++;
			x++;
		}
		y++;
	}
	if (count_p != 1 || count_e != 1 || count_c < 1)
		error_exit("Map must have 1 P, 1 E, and at least 1 C", game);
	game->collectibles = count_c;
	check_walls(game);
}
