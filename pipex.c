/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/16 18:28:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(int fds[], char **argv, char *path);
static void	parent(int fds[], char **argv, char *path);

struct s_buffers buffers;

int	main(int argc, char **argv, char **envp)
{
	int		fds[4]; //infile, outfile, pipe read, pipe write
	int		id;
	char	*path;

	if (argc < 5 || pipe(fds + 2) == -1)
		error();
	while (ft_strncmp(*envp, "PATH", 4))
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

	close(fds[2]);
	if (dup2(fds[3], STDOUT_FILENO) == -1)
		error();
	close(fds[3]);
	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] == -1)
		error();
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	cmd_args = split(argv[2], ' ');
	buffers.cmd_args_child = cmd_args;
	cmd_path = find_cmd(path, cmd_args[0]);
	buffers.cmd_path_child = cmd_path;
	execve(cmd_path, cmd_args, environ);
	error();
}

static void	parent(int fds[], char **argv, char *path)
{
	char	**cmd_args;
	char	*cmd_path;

	close(fds[3]);
	waitpid(0, NULL, 0);
	dup2(fds[2], STDIN_FILENO);
	close(fds[2]);
	cmd_args = split(argv[3], ' ');
	buffers.cmd_args_parent = cmd_args;
	cmd_path = find_cmd(path, cmd_args[0]);
	buffers.cmd_path_parent = cmd_path;
	fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] == -1)
		error();
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	execve(cmd_path, cmd_args, environ);
	error();
}
