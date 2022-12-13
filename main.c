/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:44:19 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/13 18:15:51 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	size_t	fd;
	char	*ptr;
	int		n = 0;

	fd = open("coucou.txt", O_RDONLY);
	while (n++ < 2)
	{
	ptr = (get_next_line(fd));
	printf("%s\n", ptr);
	}
	close(fd);
	free(ptr);
	return (0);
}
