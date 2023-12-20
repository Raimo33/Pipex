/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/20 15:50:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// #include "pipex_utils.c"
// #include "general_utils.c"

static void	init(int fds[]);
static void	handle_command(char **argv, char *path, char **envp, int fds[]);
static void	handle_pipe(int fds[], char **argv, char *path, char **envp);
static char *get_path(char **envp);

struct s_buffers	buffers;

// int main(void)
// {
// 	char *argv[] = {"./pipex", "infile", "ls -l", "wc -w", "outfile", NULL};
// 	char *envp[] = {"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", NULL};
// 	main2(5, argv, envp);
// }

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	int 	fds[4]; // infile, outfile, pipe read, pipe write

	init(fds);
	if (argc < 5)
		quit("wrong number of arguments", 25);
	path = get_path(envp);
	fds[0] = open(*(++argv), O_RDONLY);
	fds[1] = open(argv[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[0] == -1 || fds[1] == -1)
		quit(NULL, 0);
	while (argc-- > 4)
		handle_command(++argv, path, envp, fds);
	while (wait(NULL) > 0)
		;
	if (errno != ECHILD)
		quit(NULL, 0);
	handle_pipe(fds, argv + 1, path, envp);
	quit(NULL, 0);
}

static void	init(int fds[])
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

static void	handle_command(char **argv, char *path, char **envp, int fds[])
{
	pid_t	id;
	int		exit_status;

	if (pipe(fds + 2) == -1)
		quit(NULL, 0);
	id = fork();
	if (id == -1)
		quit(NULL, 0);
	if (id == 0)
		handle_pipe(fds, argv, path, envp);
	else
	{
		wait(&exit_status);
		errno = WEXITSTATUS(exit_status);
		if (errno != 0 || close(fds[0]) == -1 || close(fds[3]) == -1)
			quit(NULL, 0);
		fds[0] = fds[2];
	}
}

static void	handle_pipe(int fds[], char **argv, char *path, char **envp)
{
	if (*(argv + 2) == NULL)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1 || close(fds[0]) == -1)
			quit(NULL, 0);
	}
	else
		if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[3], STDOUT_FILENO) == -1 || close(fds[3]) == -1 || close(fds[0]) == -1)
			quit(NULL, 0);
	buffers.cmd_args = ft_split(*argv, ' ');
	buffers.cmd_path = find_cmd(path, buffers.cmd_args[0]);
	if (execve(buffers.cmd_path, buffers.cmd_args, envp) == -1)
		quit(NULL, 0);
}

static char *get_path(char **envp)
{
	while (envp && *envp)
		if (ft_strncmp(*envp++, "PATH=", 5) == 0)
			return (*(envp - 1) + 5);
	quit("PATH not found", 15);
	return (NULL);
}
