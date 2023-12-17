/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/17 19:06:21 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void			child(int fds[], char **argv, char *path);
static void			parent(int fds[], char **argv, char *path);

struct s_buffers	buffers;

int	main(int argc, char **argv, char **envp)
{
	int		id;
	char	*path;

	int fds[4]; // infile, outfile, pipe read, pipe write
	if (argc < 5 || pipe(fds + 2) == -1)
		error(1);
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	path = *envp + 5;
	id = fork();
	if (id == -1)
		error(2);
	if (id == 0)
		child(fds, argv, path);
	else
		parent(fds, argv, path);
	error(0);
}

static void	child(int fds[], char **argv, char *path)
{
	char	**cmd_args;
	char	*cmd_path;

	if (close(fds[2]) == -1 || dup2(fds[3], STDOUT_FILENO) == -1 || close(fds[3]) == -1)
		error(3);
	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] == -1 || dup2(fds[0], STDIN_FILENO) == -1 || close(fds[0]) == -1)
		error(4);
	cmd_args = ft_split(argv[2], ' ');
	buffers.cmd_args_child = cmd_args;
	cmd_path = find_cmd(path, cmd_args[0]);
	buffers.cmd_path_child = cmd_path;
	if (execve(cmd_path, cmd_args, environ) == -1)
		error(5);
}

static void	parent(int fds[], char **argv, char *path)
{
	char	**cmd_args;
	char	*cmd_path;

	if (close(fds[3]) || waitpid(0, NULL, 0) == -1 || dup2(fds[2], STDIN_FILENO) == -1 || close(fds[2]) == -1)
		error(6);
	cmd_args = ft_split(argv[3], ' ');
	buffers.cmd_args_parent = cmd_args;
	cmd_path = find_cmd(path, cmd_args[0]);
	buffers.cmd_path_parent = cmd_path;
	fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] == -1 || dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1 || execve(cmd_path, cmd_args, environ) == -1)
		error(7);
}
