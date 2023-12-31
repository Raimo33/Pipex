/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:03:03 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 15:11:14 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

struct s_buffers	g_buffers;

int	main(int argc, char **argv, char **envp)
{
	int		fds[4];
	char	*path;

	init(fds);
	if (argc != 5)
		quit(1, "wrong number of arguments", 26);
	path = get_path(envp);
	fds[0] = open(*(++argv), O_RDONLY);
	fds[1] = open(argv[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[0] == -1 || fds[1] == -1)
		quit(2, NULL, 0);
	handle_command(fds, ++argv, path, envp);
	wait_child();
	handle_pipe(fds, argv + 1, path, envp);
}
