/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:44:19 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/15 14:47:58 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;
	//int	fd2;
	char	*ptr;
	//char	*ptr2;
	int		n;

	n = 0;
	fd = open("coucou.txt", O_RDONLY);
	//fd2 = open("hello.txt", O_RDONLY);
	while (n++ < 4)
	{
		ptr = (get_next_line(fd));
		//ptr2 = (get_next_line(fd2));
		printf("%s", ptr);
		//printf("%s === hello!\n", ptr2);
	}
	close(fd);
	//close(fd2);
	free(ptr);
	//free(ptr2);
	return (0);
}
