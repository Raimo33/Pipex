/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/22 12:53:59 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// #include "pipex_utils.c"
// #include "general_utils.c"

static void	init(int fds[]);
static void	handle_command(int fds[], char **argv, char *path, char **envp);
static void	handle_pipe(int fds[], char **argv, char *path, char **envp);
static char *get_path(char **envp);

struct s_buffers	buffers;

// int main(void)
// {
// 	char *argv[] = {"./pipex", "infile", "grep hello", "wc -l", "outfile", NULL};
// 	char *envp[] = {"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", NULL};
// 	main2(5, argv, envp);
// }

int	main(int argc, char **argv, char **envp)
{
	int 			fds[4]; // infile, outfile, pipe read, pipe write
	t_pcs			*processes;
	unsigned int	i;
	pid_t			id;
	char			*path;

	init(fds);
	if (argc < 5)
		quit("wrong number of arguments", 26);
	path = get_path(envp);
	fds[0] = open(*(++argv), O_RDONLY);
	fds[1] = open(argv[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[0] == -1 || fds[1] == -1)
		quit(NULL, 0);
	processes = malloc(sizeof(t_pcs) * (argc - 4));
	if (!processes)
		quit("failed to allocate memory", 26);
	buffers.processes = processes;
	i = -1;
	while (++i < argc - 4)
	{
		handle_command(fds, ++argv, path, envp);
		if (pipe(fds + 2) == -1)
			quit(NULL, 0);
		id = fork();
		if (id == -1)
			quit(NULL, 0);
		if (id == 0)
			handle_pipe(fds, argv, path, envp);
		else
		{
			if (close(fds[0]) == -1 || close(fds[3]) == -1)
				quit(NULL, 0);
			fds[0] = fds[2];
			processes[i].pid = id;
			processes[i].cmd = *argv;
		}
	}
	i = -1;
	while (++i < argc - 4)
		if (waitpid(processes[i].pid, &processes[i].exit_status, 0) == -1 || !check_error(processes[i]))
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
	buffers.processes = NULL;
}

static void	handle_command(int fds[], char **argv, char *path, char **envp)
{
	pid_t	id;


}

static void	handle_pipe(int fds[], char **argv, char *path, char **envp)
{
	if (*(argv + 2) == NULL)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1 || close(fds[0]) == -1)
			quit(NULL, 0);
	}
	else if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[3], STDOUT_FILENO) == -1 || close(fds[3]) == -1 || close(fds[0]) == -1)
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
