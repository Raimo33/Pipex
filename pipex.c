/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/19 20:50:13 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// #include "pipex_utils.c"

static void	handle_pipe(int fds[], char **argv, char *path, char **envp);

struct s_buffers	buffers;

// int main(void)
// {
// 	char *argv[] = {"./pipex", "infile", "ls -l", "wc -w", "outfile", NULL};
// 	char *envp[] = {"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", NULL};
// 	main2(5, argv, envp);
// }

int	main(int argc, char **argv, char **envp)
{
	pid_t			id;
	char			*path;
	int 			fds[4]; // infile, outfile, pipe read, pipe write
	unsigned int	i;

	if (argc < 5)
		quit(1);
	/////////////////////////////////////////
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	path = envp[i] + 5;
	/////////////////////////////////////////
	fds[0] = open(*(++argv), O_RDONLY);
	fds[1] = open(argv[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	buffers.fds = fds;
	if (fds[0] == -1 || fds[1] == -1)
		quit(2);
	while (argc-- > 4)
	{
		//////////////////////////////////////
		if (pipe(fds + 2) == -1)
			quit(3);
		id = fork();
		if (id == -1)
			quit(4);
		++argv;
		if (id == 0)
			handle_pipe(fds, argv, path, envp);
		if (close(fds[0]) == -1 || close(fds[3]) == -1)
			quit(5);
		fds[0] = fds[2];
		//////////////////////////////////////
	}
	while (wait(NULL) > 0)
		;
	if (errno != ECHILD)
		quit(6);
	handle_pipe(fds, argv + 1, path, envp);
	quit(0);
}

static void	handle_pipe(int fds[], char **argv, char *path, char **envp)
{
	if (*(argv + 2) == NULL)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1 || close(fds[0]) == -1)
			quit(7);
	}
	else
		if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[3], STDOUT_FILENO) == -1 || close(fds[3]) == -1 || close(fds[0]) == -1)
			quit(8);
	buffers.cmd_args = ft_split(*argv, ' ');
	buffers.cmd_path = find_cmd(path, buffers.cmd_args[0]);
	if (execve(buffers.cmd_path, buffers.cmd_args, envp) == -1)
		quit(9);
}
