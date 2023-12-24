/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:25:21 by craimond          #+#    #+#             */
/*   Updated: 2023/12/24 14:33:44 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(int fds[])
{
	fds[0] = -1;
	fds[1] = -1;
	fds[2] = -1;
	fds[3] = -1;
	buffers.fds = fds;
	buffers.str_array = NULL;
	buffers.cmd_args = NULL;
	buffers.cmd_path = NULL;
}

void	handle_command(int fds[], char **argv, char *path, char **envp)
{
	pid_t	id;
	
	if (pipe(fds + 2) == -1)
		quit(7, NULL, 0);
	id = fork();
	if (id == -1)
		quit(8, NULL, 0);
	if (id == 0)
		handle_pipe(fds, argv, path, envp);
	else
	{
		if (close(fds[0]) == -1 || close(fds[3]) == -1)
			quit(9, NULL, 0);
		fds[0] = fds[2];
	}
}

void	handle_pipe(int fds[], char **argv, char *path, char **envp)
{
	if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[3], STDOUT_FILENO) == -1 || close(fds[3]) == -1 || close(fds[0]) == -1)
		quit(42 + errno, "", 0);
	buffers.cmd_args = ft_split(*argv, ' ');
	buffers.cmd_path = find_cmd(path, buffers.cmd_args[0]);
	if (execve(buffers.cmd_path, buffers.cmd_args, envp) == -1)
		quit(42 + errno, "", 0);
}

void	last_pipe(int fds[], char **argv, char *path, char **envp)
{
	if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1 || close(fds[0]) == -1)
		quit(8, "", 0);
	buffers.cmd_args = ft_split(*argv, ' ');
	buffers.cmd_path = find_cmd(path, buffers.cmd_args[0]);
	if (execve(buffers.cmd_path, buffers.cmd_args, envp) == -1)
		quit(3, "", 0);
}

void	wait_child(void)
{
	int		status;

	if (wait(&status) == -1)
		quit(3, NULL, 0);
	if (WIFSIGNALED(status))
		quit(WTERMSIG(status) + 128, "process interrupted by a signal", 32);
	else
	{
		status = WEXITSTATUS(status);
		if (status > 42)
		{
			errno = status - 42;
			quit(4, NULL, 0);
		}
	}
}
