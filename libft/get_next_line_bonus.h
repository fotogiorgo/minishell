/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:57:32 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/01 20:34:11 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct variables {
	int			ret_size;
	char		*buf;
	char		*ret;
	int			line_bytes;
	int			found_nl;
	int			bytes_read;
}				t_vars;

size_t	ft_strlen(const char *s);
char	*strjoin(char *s1, int s1_len, char *s2, int s2_len);
void	ft_bzero(void *str, size_t n);
char	*get_next_line(int fd);
#endif