#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	char	*content;
	int		height;

	init_game(&game);
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./so_long <map.ber>\n", 2);
		return (1);
	}
	if (!is_ber_file(argv[1]))
		error_exit("Map must have .ber extension", &game);
	content = read_file(argv[1]);
	if (!content)
		error_exit("Failed to read map", &game);
	game.map = split_map(content, &height);
	(void)height;
	free(content);
	if (!game.map)
		error_exit("Invalid map format", &game);
	validate_map(&game);
	check_path(&game);
	game.map[game.player_y][game.player_x] = '0';
	game.mlx = mlx_init();
	if (!game.mlx)
		error_exit("Failed to init MLX", &game);
	game.win = mlx_new_window(game.mlx, game.width * TILE_SIZE,
			game.height * TILE_SIZE, "so_long");
	if (!game.win)
		error_exit("Failed to create window", &game);
	load_textures(&game);
	render_map(&game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	mlx_loop(game.mlx);
	return (0);
}
