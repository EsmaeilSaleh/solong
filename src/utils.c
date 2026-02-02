/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 07:48:42 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/02 07:48:44 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->player_x = -1;
	game->player_y = -1;
	game->exit_x = -1;
	game->exit_y = -1;
}

int	is_ber_file(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".ber", 4) == 0);
}

void	print_move_count(int moves)
{
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(moves, 1);
	ft_putstr_fd("\n", 1);
}
