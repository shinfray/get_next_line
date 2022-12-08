/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:44:19 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/08 18:18:06 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	//char	str1[] = "coucoukkk";
	//char	str2[] = " hello";

//	printf("%s\n", ft_strnjoin(str1, str2, 50));
	size_t	fd;

	fd = open("coucou", O_RDONLY);
	printf("%s\n", get_next_line(fd));

	return (0);
}
