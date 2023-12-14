/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:44 by craimond          #+#    #+#             */
/*   Updated: 2023/12/14 19:56:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_read_all(int fd);

int	main(int argc, char **argv)
{
	int		fd[2];
	int		id;
	char	*out;

	buffers.out = out;
	if (pipe(fd) == -1)
		error();
	id = fork();
	if (id == -1)
		error();
	if (id == 0)
	{
		out = ft_read_all(fd[0]);
	}
}

static char	*ft_read_all(int fd)
{
	char			*buf;
	char			*tot;
	char			*tmp;
	unsigned int	i;
	unsigned int	j;

	j = 1;
	tmp = NULL;
	while (1)
	{
		if (read(fd, buf, 0) == -1) //error
			error();
		buf = malloc(BUFFER_SIZE);
		buffers.buf = buf;
		if (!buf)
			error();
		if (!read(fd, buf, BUFFER_SIZE)) //EOF
			break ;
		tmp = tot;
		tot = malloc(BUFFER_SIZE * j++ + 1);
		if (!tot)
			error();
		buffers.tot = tot;
		i = -1;
		while(tmp && tmp[++i])
			tot[i] = tmp[i];
		free(tmp); //inizializare tmp a NULL se da invalid free
		i--;
		while (buf[++i])
			tot[i] = buf[i];
		tot[i] = '\0';
		free(buf);
	}
	free(buf);
	return (tot);
}