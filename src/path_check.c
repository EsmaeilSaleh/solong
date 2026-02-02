#include "so_long.h"

typedef struct s_point
{
	int	x;
	int	y;
} 	t_point;

void	check_path(t_game *game)
{
	int		max;
	char	*visited;
	t_point	*queue;
	int		head;
	int		tail;
	int		reachable_c;
	int		reachable_e;
	int		i;
	int		nx;
	int		ny;
	int		dx[4];
	int		dy[4];

	max = game->width * game->height;
	visited = (char *)ft_calloc(max, sizeof(char));
	queue = (t_point *)malloc(sizeof(t_point) * max);
	if (!visited || !queue)
	{
		free(visited);
		free(queue);
		error_exit("Memory allocation failed", game);
	}
	head = 0;
	tail = 0;
	reachable_c = 0;
	reachable_e = 0;
	queue[tail++] = (t_point){game->player_x, game->player_y};
	visited[game->player_y * game->width + game->player_x] = 1;
	dx[0] = 1;
	dx[1] = -1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
	while (head < tail)
	{
		t_point cur = queue[head++];
		i = 0;
		while (i < 4)
		{
			nx = cur.x + dx[i];
			ny = cur.y + dy[i];
			if (nx >= 0 && nx < game->width && ny >= 0 && ny < game->height)
			{
				if (!visited[ny * game->width + nx]
					&& game->map[ny][nx] != '1')
				{
					visited[ny * game->width + nx] = 1;
					queue[tail++] = (t_point){nx, ny};
					if (game->map[ny][nx] == 'C')
						reachable_c++;
					else if (game->map[ny][nx] == 'E')
						reachable_e = 1;
				}
			}
			i++;
		}
	}
	free(visited);
	free(queue);
	if (reachable_c != game->collectibles || !reachable_e)
		error_exit("Map has no valid path", game);
}
