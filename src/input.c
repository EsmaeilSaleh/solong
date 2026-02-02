/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 07:19:33 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/02 07:19:45 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	try_move(t_game *game, int dx, int dy)
{
	int		nx;
	int		ny;
	char	tile;

	nx = game->player_x + dx;
	ny = game->player_y + dy;
	if (nx < 0 || ny < 0 || nx >= game->width || ny >= game->height)
		return ;
	tile = game->map[ny][nx];
	if (tile == '1')
		return ;
	game->moves++;
	print_move_count(game->moves);
	if (tile == 'C')
	{
		game->collected++;
		game->map[ny][nx] = '0';
	}
	game->player_x = nx;
	game->player_y = ny;
	if (tile == 'E' && game->collected == game->collectibles)
	{
		render_map(game);
		handle_close(game);
	}
	render_map(game);
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		try_move(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		try_move(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		try_move(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		try_move(game, 1, 0);
	return (0);
}
