/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/15 15:51:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(int fds[], char **argv);
static void	parent(int fds[], char **argv);

int	main(int argc, char **argv)
{
	int		fds[2];
	int		id;

	if (argc < 5)
		error();
	if (pipe(fds) == -1)
		error();
	id = fork();
	if (id == -1)
		error();
	/////////////////////////////
	if (id == 0)
		child(fds, argv);
	else
		parent(fds, argv);
	free(buffers.path_child);
	free(buffers.path_parent);
	free_matrix(buffers.cmd_args_child);
	free_matrix(buffers.cmd_args_parent);
	/////////////////////////////
}

static void	child(int fds[], char **argv)
{
	char	*cmd_args;
	char	*path;

	close(fds[0]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		error();
	close(fds[1]);
	cmd_args = split(argv + 2, ' ');
	buffers.cmd_args_child = cmd_args;
	path = find_path(cmd_args[0]);
	buffers.path_child = path;
	execve(path, cmd_args, environ);
	error();
}

static void	parent(int fds[], char **argv)
{
	char	*out;
	char	*cmd_args;
	char	*path;
	char	*full_input;

	close(fds[1]);
	waitpd(0, NULL, 0);
	out = ft_read_all(fds[0]);
	close(fds[0]);
	full_input = strjoin(argv + 3, out);
	buffers.full_input = full_input;
	cmd_args = split(full_input, ' ');
	free(full_input);
	buffers.cmd_args_parent = cmd_args;
	path = find_path(cmd_args[0]);
	buffers.path_child = path;
	execve(path, cmd_args, environ);
	error();
}
