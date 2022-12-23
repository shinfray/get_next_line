/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:19:18 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/23 14:26:06 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		n;
	char	*ptr;

	n = 0;
	fd = open("hello.txt", O_RDONLY);
	while (n++ < 12)
	{
		ptr = (get_next_line(fd));
		printf("=== hello : %s", ptr);
	}
	close(fd);
	free(ptr);
	return (0);
}
