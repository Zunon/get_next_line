/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:16:56 by kalmheir          #+#    #+#             */
/*   Updated: 2022/02/21 07:28:29 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_fd_map
{
	struct s_fd_map	*prev;
	struct s_fd_map	*next;
	int				*fd;
	char			*buffer;
}	t_fd_map;
char		*ft_strjoin2(char *str1, char *str2, int free2);
char		*ft_strchr(char *s, int c);
char		*get_next_line(int fd);
t_fd_map	*fd_lstnew(int *fd);
t_fd_map	*fd_lstget(t_fd_map **fd_list, int fd);
char		*ft_substr_unsafe(char *s, unsigned int start, size_t len);
t_fd_map	*get_fd(int fd, t_fd_map **fd_list);
char		*returner(char *newline, t_fd_map **current, char *result);
void		fd_lstdelone(t_fd_map *lst);
char		*iterator(char **r, int *re, t_fd_map **current, int fd);
char		*end(t_fd_map **current, t_fd_map **fd_list, char **result);
#endif
