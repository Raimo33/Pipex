/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:51 by craimond          #+#    #+#             */
/*   Updated: 2023/12/22 12:30:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_process
{
	pid_t	pid;
	char	*cmd;
	int		exit_status
}					t_pcs;

struct s_buffers
{
	t_pcs	*processes;
	int		*fds;
	char	**str_array;
	char	**cmd_args;
	char	*cmd_path;
};

extern struct s_buffers	buffers;

void	quit(char *msg, unsigned short len);
char	check_error(t_pcs process);
int		ft_atoi(char *nptr);
int		ft_nbrlen(int n);
char	**ft_split(char *s, char c);
char	*find_cmd(char *path, char *cmd);
char	ft_strncmp(char *s1, char *s2, int n);
char	*ft_strncpy(char *dest, char *src, int n);

#endif