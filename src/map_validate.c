/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 07:48:16 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/02 07:48:19 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

static void	check_dimensions(t_game *game)
{
	game->height = 0;
	while (game->map[game->height])
		game->height++;
	game->width = (int)ft_strlen(game->map[0]);
	if (game->width <= 0 || game->height <= 0)
		error_exit("Map is empty", game);
}

static void	handle_tile(t_game *game, t_counts *counts, t_point pos)
{
	char	tile;

	tile = game->map[pos.y][pos.x];
	if (!is_valid_char(tile))
		error_exit("Map has invalid characters", game);
	if (tile == 'P')
	{
		game->player_x = pos.x;
		game->player_y = pos.y;
		counts->p++;
	}
	else if (tile == 'E')
	{
		game->exit_x = pos.x;
		game->exit_y = pos.y;
		counts->e++;
	}
	else if (tile == 'C')
		counts->c++;
}

static void	validate_row(t_game *game, t_counts *counts, int y)
{
	int		x;
	t_point	pos;

	if ((int)ft_strlen(game->map[y]) != game->width)
		error_exit("Map must be rectangular", game);
	x = 0;
	while (x < game->width)
	{
		pos.x = x;
		pos.y = y;
		handle_tile(game, counts, pos);
		x++;
	}
}

void	validate_map(t_game *game)
{
	int			y;
	t_counts	counts;

	check_dimensions(game);
	counts.p = 0;
	counts.e = 0;
	counts.c = 0;
	y = 0;
	while (y < game->height)
	{
		validate_row(game, &counts, y);
		y++;
	}
	if (counts.p != 1 || counts.e != 1 || counts.c < 1)
		error_exit("Map must have 1 P, 1 E, and at least 1 C", game);
	game->collectibles = counts.c;
	check_walls(game);
}
