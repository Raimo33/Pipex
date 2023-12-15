/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/15 19:08:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(int fds[], char **argv, char *path);
static void	parent(int fds[], char **argv, char *path);

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	int		id;
	char	*path;

	if (argc < 5 || pipe(fds) == -1)
		error();
	while (strncmp(*envp, "PATH", 4))
		envp++;
	path = *envp + 5;
	id = fork();
	if (id == -1)
		error();
	if (id == 0)
		child(fds, argv, path);
	else
		parent(fds, argv, path);
	free(buffers.path_child);
	free(buffers.path_parent);
	free_matrix(buffers.cmd_args_child);
	free_matrix(buffers.cmd_args_parent);
}

static void	child(int fds[], char **argv, char *path)
{
	char	**cmd_args;
	char	*cmd_path;

	close(fds[0]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		error();
	close(fds[1]);
	cmd_args = split(argv[2], ' ');
	buffers.cmd_args_child = cmd_args;
	cmd_path = find_cmd(path, cmd_args[0]);
	buffers.cmd_path_child = cmd_path;
	execve(cmd_path, cmd_args, environ);
	error();
}

static void	parent(int fds[], char **argv, char *path)
{
	char	*out;
	char	**cmd_args;
	char	*cmd_path;
	char	*full_input;

	close(fds[1]);
	waitpid(0, NULL, 0);
	out = ft_read_all(fds[0]);
	close(fds[0]);
	full_input = strjoin(argv[3], out);
	free(out);
	buffers.full_input = full_input;
	cmd_args = split(full_input, ' ');
	free(full_input);
	buffers.cmd_args_parent = cmd_args;
	cmd_path = find_cmd(path, cmd_args[0]);
	buffers.cmd_path_parent = cmd_path;
	execve(cmd_path, cmd_args, environ);
	error();
}
