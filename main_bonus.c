/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:56:54 by craimond          #+#    #+#             */
/*   Updated: 2023/12/24 14:34:27 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

struct s_buffers	buffers;

int	main(int argc, char **argv, char **envp)
{
	int 			fds[4]; // infile, outfile, pipe read, pipe write
	int				i;
	char			*path;

	init(fds);
	if (argc < 5)
		quit(1, "wrong number of arguments", 26);
	path = get_path(envp);
	if (ft_strncmp(*(++argv), "here_doc", 8) == 0)
		handle_here_doc(fds, ++argv, --argc);
	else
	{
		fds[0] = open(*argv, O_RDONLY);
		fds[1] = open(argv[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fds[0] == -1 || fds[1] == -1)
		quit(2, NULL, 0);
	i = argc;
	while (argc-- > 4)
		handle_command(fds, ++argv, path, envp);
	while (i-- > 4)
		wait_child();
	last_pipe(fds, argv + 1, path, envp);
	quit(0, NULL, 0);
}