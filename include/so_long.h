/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 08:30:17 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/02 08:30:20 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# define TILE_SIZE 32

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_img
{
	void	*img;
	int		w;
	int		h;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		collectibles;
	int		collected;
	int		moves;
	t_img	wall;
	t_img	floor;
	t_img	player;
	t_img	exit;
	t_img	collect;
}	t_game;

typedef struct s_buf
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_buf;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_bfs
{
	char	*visited;
	t_point	*queue;
	int		head;
	int		tail;
	int		reachable_c;
	int		reachable_e;
	int		max;
}	t_bfs;

typedef struct s_counts
{
	int	p;
	int	e;
	int	c;
}	t_counts;

void	error_exit(const char *msg, t_game *game);
void	init_game(t_game *game);

int		is_ber_file(const char *path);
int		is_valid_char(char c);
char	*read_file(const char *path);
char	**split_map(const char *content, int *height);
void	free_map(char **map);

void	validate_map(t_game *game);
void	check_path(t_game *game);

void	load_textures(t_game *game);
void	destroy_textures(t_game *game);
void	render_map(t_game *game);

int		handle_key(int keycode, t_game *game);
int		handle_close(t_game *game);

void	print_move_count(int moves);

#endif
