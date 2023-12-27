/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:27:08 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 15:18:32 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*str;
	char		*ret;
	char		*buf;
	static char	*ptr;
	int			out;

	out = -42;
	while ((out > 0 && ptr) || out == -42)
	{
		str = ft_calloc(B_SIZE + 1, 1);
		if (!str)
			break ;
		out = read(fd, str, B_SIZE);
		buf = f_strjoin(ptr, str);
		ptr = buf;
		ret = get_single_line(ptr);
		if (ft_strlen(ret) > 0
			&& (ret[ft_strlen(ret) - 1] == '\n' || (out < B_SIZE && out >= 0)))
		{
			ptr += ft_strlen(ret) + (*buf == -42);
			return (ret);
		}
		free(ret);
	}
	return (free_and_null(buf, &ptr));
}
