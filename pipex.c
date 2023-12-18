/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/18 20:21:00 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(int fds[], char **argv, char *path);
// static void			last_pipe(int fds[], char **argv, char *path);

struct s_buffers	buffers;

int	main(int argc, char **argv, char **envp)
{
	pid_t			id;
	char			*path;
	int 			fds[4]; // infile, outfile, pipe read, pipe write
	int				prev_out;
	int				tmp;

	if (argc < 5)
		quit(1);
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	path = *envp + 5;
	fds[0] = open(++*argv, O_RDONLY);
	fds[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	buffers.fds = fds;
	if (fds[0] == -1 || fds[1] == -1)
		quit(2);
	while (argc-- > 4)
	{
		id = fork();
		if (id == -1 || pipe(fds + 2) == -1)
			quit(3);
		if (id == 0)
			child(fds, ++argv, path);
		if (close(fds[3]) == -1 || close(fds[0]) == -1)
			quit(4);
		fds[0] = fds[2];
		free_matrix(buffers.cmd_args);
		free(buffers.cmd_path);
	}
	while (wait(NULL) > 0)
		;
	if (errno != ECHILD)
		quit(5);
	child(fds, argv, path);
	quit(0);
}

static void	child(int fds[], char **argv, char *path)
{
	if (close(fds[2]) == -1 || dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[3], STDOUT_FILENO) == -1 || close(fds[3]) == -1 || close(fds[0]) == -1)
		quit(6);
	buffers.cmd_args = ft_split(*argv, ' ');
	buffers.cmd_path = find_cmd(path, buffers.cmd_args[0]);
	if (*(argv + 1) == NULL)
		if (dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1)
			quit(9);
	if (execve(buffers.cmd_path, buffers.cmd_args, environ) == -1)
		quit(7);
}

// static void	last_pipe(int fds[], char **argv, char *path)
// {
// 	char	**cmd_args;
// 	char	*cmd_path;

// 	if (close(fds[3]) || dup2(fds[2], STDIN_FILENO) == -1 || close(fds[2]) == -1)
// 		quit(8);
// 	cmd_args = ft_split(*argv, ' ');
// 	buffers.cmd_args = cmd_args;
// 	cmd_path = find_cmd(path, cmd_args[0]);
// 	buffers.cmd_path = cmd_path;
// 	fds[1] = open(*argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fds[1] == -1 || dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1 || execve(cmd_path, cmd_args, environ) == -1)
// 		quit(9);
// }
