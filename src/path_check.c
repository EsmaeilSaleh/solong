/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 07:48:26 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/02 08:20:34 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_bfs(t_game *game, t_bfs *bfs)
{
	bfs->max = game->width * game->height;
	bfs->visited = (char *)ft_calloc(bfs->max, sizeof(char));
	bfs->queue = (t_point *)malloc(sizeof(t_point) * bfs->max);
	if (!bfs->visited || !bfs->queue)
	{
		free(bfs->visited);
		free(bfs->queue);
		error_exit("Memory allocation failed", game);
	}
	bfs->head = 0;
	bfs->tail = 0;
	bfs->reachable_c = 0;
	bfs->reachable_e = 0;
	bfs->queue[0] = (t_point){game->player_x, game->player_y};
	bfs->tail = 1;
	bfs->visited[game->player_y * game->width + game->player_x] = 1;
}

static void	visit_neighbors(t_game *game, t_bfs *bfs, t_point cur)
{
	static const int	dx[4] = {1, -1, 0, 0};
	static const int	dy[4] = {0, 0, 1, -1};
	int					i;
	int					nx;
	int					ny;

	i = 0;
	while (i < 4)
	{
		nx = cur.x + dx[i];
		ny = cur.y + dy[i];
		if (nx >= 0 && nx < game->width && ny >= 0 && ny < game->height
			&& !bfs->visited[ny * game->width + nx]
			&& game->map[ny][nx] != '1')
		{
			bfs->visited[ny * game->width + nx] = 1;
			bfs->queue[bfs->tail++] = (t_point){nx, ny};
			bfs->reachable_c += (game->map[ny][nx] == 'C');
			bfs->reachable_e |= (game->map[ny][nx] == 'E');
		}
		i++;
	}
}

static void	run_bfs(t_game *game, t_bfs *bfs)
{
	t_point	cur;

	while (bfs->head < bfs->tail)
	{
		cur = bfs->queue[bfs->head];
		bfs->head++;
		visit_neighbors(game, bfs, cur);
	}
}

static void	free_bfs(t_bfs *bfs)
{
	free(bfs->visited);
	free(bfs->queue);
}

void	check_path(t_game *game)
{
	t_bfs	bfs;

	init_bfs(game, &bfs);
	run_bfs(game, &bfs);
	free_bfs(&bfs);
	if (bfs.reachable_c != game->collectibles || !bfs.reachable_e)
		error_exit("Map has no valid path", game);
}
