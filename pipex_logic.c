/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:25:21 by craimond          #+#    #+#             */
/*   Updated: 2023/12/24 17:03:59 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	reset_fd(int *fd);

void	init(int fds[])
{
	fds[0] = -1;
	fds[1] = -1;
	fds[2] = -1;
	fds[3] = -1;
	buffers.fds = fds;
	buffers.str_array = NULL;
	buffers.cmd_path = NULL;
}

void	handle_command(int fds[], char **argv, char *path, char **envp)
{
	pid_t	id;
	
	if (pipe(fds + 2) == -1)
		quit(3, NULL, 0);
	id = fork();
	if (id == -1)
		quit(4, NULL, 0);
	if (id == 0)
		handle_pipe(fds, argv, path, envp);
	else
	{
		if (reset_fd(&fds[0]) == -1 || reset_fd(&fds[3]) == -1)
			quit(5, NULL, 0);
		fds[0] = fds[2];
	}
}

void	handle_pipe(int fds[], char **argv, char *path, char **envp)
{
	char	error_msg[50];
	int		out_fd;

	out_fd = 1 * (!*(argv + 2)) + 3 * (*(argv + 2) != NULL);
	if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[out_fd], STDOUT_FILENO) == -1 || reset_fd(&fds[out_fd]) == -1 || reset_fd(&fds[0]) == -1)
		quit(42, NULL, 0);
	buffers.cmd_args = ft_split(*argv, ' ');
	buffers.cmd_path = find_cmd(path, buffers.cmd_args[0]);
	if (!buffers.cmd_path)
	{
		error_msg[0] = '\0';
		ft_strcat(error_msg, "command not found: ");
		ft_strcat(error_msg, buffers.cmd_args[0]);
		quit(43, error_msg, ft_strlen(error_msg));
	}
	if (execve(buffers.cmd_path, buffers.cmd_args, envp) == -1)
		quit(44, NULL, 0);
}

void	wait_child(void)
{
	int		status;

	if (wait(&status) == -1)
		quit(6, NULL, 0);
	if (WIFSIGNALED(status))
		quit(WTERMSIG(status) + 128, "process interrupted by a signal", 32);
	else
	{
		status = WEXITSTATUS(status);
		if (status >= 42 && status <= 44)
			exit(status);
	}

}

static char reset_fd(int *fd)
{
	if (close(*fd) == -1)
		return (-1);
	*fd = -1;
	return (0);
}
