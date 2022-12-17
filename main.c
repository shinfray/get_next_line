/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:44:19 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/17 21:00:26 shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		fd2;
	int		n;
	char	*ptr;
	char	*ptr2;

	n = 0;
	fd = open("hello.txt", O_RDONLY);
	fd2 = open("coucou.txt", O_RDONLY);
	while (n++ < 12)
	{
		ptr = (get_next_line(fd));
		printf("=== hello : %s", ptr);
	}
	n = 0;
	while (n++ < 12)
	{
		ptr2 = (get_next_line(fd2));
		printf("=== coucou : %s", ptr2);
	}
	close(fd);
	close(fd2);
	free(ptr);
	free(ptr2);
	return (0);
}
