/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:52:04 by craimond          #+#    #+#             */
/*   Updated: 2023/12/23 21:24:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// #include "pipex_utils_bonus.c"
// #include "general_utils_bonus.c"
// #include "gnl_bonus/get_next_line.c"
// #include "gnl_bonus/get_next_line_utils.c"

static void	init(int fds[]);
static void	handle_here_doc(int fds[], char **argv, int argc);
static void	handle_command(int fds[], char **argv, char *path, char **envp);
static void	handle_pipe(int fds[], char **argv, char *path, char **envp);
static char *get_path(char **envp);
static void	wait_child(void);

struct s_buffers	buffers;

// int	main2(int argc, char **argv, char **envp);

// int main(void)
// {
// 	char *argv[] = {"./pipex", "here_doc", "CACCA", "infile", "grep hello", "wc -l", "outfile", NULL};
// 	char *envp[] = {"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", NULL};
// 	main2(7, argv, envp);
// }

int	main(int argc, char **argv, char **envp)
{
	int 			fds[4]; // infile, outfile, pipe read, pipe write
	int				i;
	char			*path;

	init(fds);
	if (argc < 5)
		quit(1, "wrong number of arguments", 26);
	path = get_path(envp);
	if (ft_strncmp(*(++argv), "here_doc", 8) == 0)
		handle_here_doc(fds, ++argv, --argc);
	else
	{
		fds[0] = open(*argv, O_RDONLY);
		fds[1] = open(argv[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fds[0] == -1 || fds[1] == -1)
		quit(2, NULL, 0);
	i = argc;
	while (argc-- > 4)
		handle_command(fds, ++argv, path, envp);
	while (i-- > 4)
		wait_child();
	handle_pipe(fds, argv + 1, path, envp);
	quit(0, NULL, 0);
}

static void wait_child(void)
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

static void	handle_here_doc(int fds[], char **argv, int argc)
{
	char	*content;
	char	*limiter;
	char	*tmp;
	char	len;

	fds[0] = open(".here_doc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds[0] == -1)
		quit(5, NULL, 0);
	limiter = *argv;
	len = ft_strlen(limiter);
	content = NULL;
    tmp = get_next_line(0);
	while (tmp && ft_strncmp(tmp, limiter, len + 1) != 0)
	{
   	 	content = ft_strjoin(content, tmp);
   		free(tmp);
    	tmp = get_next_line(0);
	}
	if (tmp && content)
		write(fds[0], content, ft_strlen(content) - 1);
	free(tmp);
	free(content);
	if (!tmp)
		quit(6, "invalid here_doc", 17);
	fds[1] = open(argv[argc - 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
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

static void	handle_command(int fds[], char **argv, char *path, char **envp)
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

static void	handle_pipe(int fds[], char **argv, char *path, char **envp)
{
	if (*(argv + 2) == NULL)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[1], STDOUT_FILENO) == -1 || close(fds[1]) == -1 || close(fds[0]) == -1)
			quit(10, "", 0);
	}
	else if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[3], STDOUT_FILENO) == -1 || close(fds[3]) == -1 || close(fds[0]) == -1)
			quit(42 + errno, "", 0);
	buffers.cmd_args = ft_split(*argv, ' ');
	buffers.cmd_path = find_cmd(path, buffers.cmd_args[0]);
	if (execve(buffers.cmd_path, buffers.cmd_args, envp) == -1)
		quit(42 + errno, "", 0);
}

static char *get_path(char **envp)
{
	while (envp && *envp)
		if (ft_strncmp(*envp++, "PATH=", 5) == 0)
			return (*(envp - 1) + 5);
	quit(11, "PATH not found", 15);
	return (NULL);
}
