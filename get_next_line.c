/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:31:18 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/07 15:20:23 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	char		*temp_buf;
	char		*line;
	ssize_t		ret;
	size_t		i;

	while (ret > 0)
	{
		i = 0;
		temp_buf = malloc(sizeof(*temp_buf) * BUFFER_SIZE);
		ret = read(fd, temp_buf);
		if (ret > 0)
			buf[fd] = malloc(sizeof(*buf[fd]) * (ret + 1));
		while (ret > 0)
		{
			buf[fd][i] = temp_buf[i];
			if (temp_buf[i] == '\n')
			{
				ft_strnjoin(line, )
			}
			else
			{
				++i;
				--ret;
			}

		}
	}


}
