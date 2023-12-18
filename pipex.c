/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/18 17:35:46 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void			child(int fds[], int prev_out, char **argv, char *path);
static void			last_pipe(int fds[], char **argv, char *path);

struct s_buffers	buffers;

int	main(int argc, char **argv, char **envp)
{
	pid_t			id;
	char			*path;
	int 			fds[4]; // infile, outfile, pipe read, pipe write
	int				prev_out;
	int				tmp;

	if (argc < 5)
		error(1);
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	path = *envp + 5;
	prev_out = open(++argv, O_RDONLY);
	if (prev_out == -1)
		error(2);
	while (argc-- > 4)
	{
		id = fork();
		if (id == -1 || pipe(fds + 2) == -1)
			error(3);
		if (id == 0)
			child(fds, prev_out, ++argv, path);
		if (close(fds[3]) == -1 || close(prev_out) == -1)
			error(4);
		prev_out = fds[2];
	}
	while (wait(NULL) > 0)
		;
	if (errno != ECHILD)
		error(5);
	last_pipe(fds, argv, path);
	error(0);
	//FARE GIT PULL DELLE MODIFICHE FATTE IERI SERA IN UTILS SPLIT (STRNCMP ETC.)
}

static void	child(int fds[], int prev_out, char **argv, char *path)
{
	char	**cmd_args;
	char	*cmd_path;

	if (close(fds[2]) == -1 || dup2(prev_out, STDIN_FILENO) == -1 || dup2(fds[3], STDOUT_FILENO) == -1 || close(fds[3]) == -1 || close(fds[0]) == -1)
		error(3);
	cmd_args = ft_split(*argv, ' ');
	buffers.cmd_args_child = cmd_args;
	cmd_path = find_cmd(path, cmd_args[0]);
	buffers.cmd_path_child = cmd_path;
	if (execve(cmd_path, cmd_args, environ) == -1)
		error(5);
}

static void	last_pipe(int fds[], char **argv, char *path)
{
	char	**cmd_args;
	char	*cmd_path;

	if (close(fds[3]) || dup2(fds[2], STDIN_FILENO) == -1 || close(fds[2]) == -1)
		error(6);
	cmd_args = ft_split(*argv, ' ');
	buffers.cmd_args_parent = cmd_args;
	cmd_path = find_cmd(path, cmd_args[0]);
	buffers.cmd_path_parent = cmd_path;
	fds[1] = open(*argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] == -1 || dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1 || execve(cmd_path, cmd_args, environ) == -1)
		error(7);
}
