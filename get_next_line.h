/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 00:11:56 by shinfray          #+#    #+#             */
/*   Updated: 2022/12/17 21:14:51 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define ERROR				-1
# define EOF_REACHED		0
# define NEWLINE_FOUND		1
# define NEWLINE_NOT_FOUND	0

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

	/* to delete before evaluation !!!!! */

char	*get_next_line(int fd);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strnjoin(char *s1, char const *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);

#endif
