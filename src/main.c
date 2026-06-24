/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retoriya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 07:59:26 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/22 22:37:01 by maono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include <X11/X.h>

static void	exit_error(t_game *game, char *msg)
{
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	if (game)
		free_game(game);
	exit(1);
}

int	set_error(t_game *game, char *msg)
{
	game->error_msg = msg;
	return (-1);
}

static void	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		exit_error(NULL, "Usage: ./cub3D <map.cub>");
	len = (int)ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		exit_error(NULL, "Map file must have .cub extension");
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->screen.win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->screen.win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->screen.win, DestroyNotify, 0, window_close, game);
	mlx_loop_hook(game->screen.mlx, frame_hook, game);
	mlx_expose_hook(game->screen.win, frame_hook, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	ft_bzero(&game, sizeof(t_game));
	if (parse_cub_file(&game, argv[1]))
		exit_error(&game, game.error_msg);
	if (init_game(&game))
		exit_error(&game, game.error_msg);
	setup_hooks(&game);
	mlx_loop(game.screen.mlx);
	free_game(&game);
	return (0);
}
