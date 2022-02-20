/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:17:01 by kalmheir          #+#    #+#             */
/*   Updated: 2022/02/21 02:56:51 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 *	Function: fd_lstnew
 *	------------------------
 *	Allocates a new node for the fd list
 *	Returns: Pointer to the allocated node
 *	fd: Pointer to the file descriptor to be added
 *	buffer: Pointer to the new buffer created
 */
t_fd_map	*fd_lstnew(int *fd, void *buffer)
{
	t_fd_map	*result;

	result = malloc(sizeof(t_fd_map));
	if (!result)
		return (0);
	result->buffer = buffer;
	result->next = 0;
	result->fd = fd;
	return (result);
}

/*
 *	Function: fd_lstget
 *	------------------------
 *	Searches through the fd list for a node containing a specific fd
 *	Returns: Pointer to the node found, NULL if none exist
 *	fd_list: List to be searched through
 *	fd: File descriptor to be found
 */
t_fd_map	*fd_lstget(t_fd_map *fd_list, int fd)
{
	if (!fd_list)
		return (0);
	while (fd_list != 0 && *(fd_list->fd) != fd)
		fd_list = fd_list->next;
	if (*(fd_list->fd) != fd)
		return (0);
	return (fd_list);
}

/*
 *	Function: ft_substr
 *	------------------------
 *	Allocates a substring from the given string
 *	Returns: Pointer to the new allocated string
 *	s: String to create a substring from
 *	start: Index of character to begin the substring from
 *	len: Length of the substring
 */
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	totlength;
	size_t	actual_length;
	char	*result;

	if (!s)
		return (0);
	totlength = ft_strlen(s);
	if (start >= totlength)
	{
		result = malloc(sizeof(char));
		if (!result)
			return (0);
		result[0] = 0;
		return (result);
	}
	if (totlength > len)
		actual_length = len;
	else
		actual_length = totlength - start;
	result = malloc((actual_length + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, s + start, actual_length + 1);
	return (result);
}

/*
 *	Function: ft_strlcpy
 *	------------------------
 *	Turns a destination string into a copy of a source string,
 *	while being memory-safe.
 *	Returns: Length of the string it tried to create
 *	dst: Destination string to be turned into a copy of src
 *	src: Source string to copy from
 *	dstsize: Maximum capacity of the destination string
 */
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dstsize)
		return (ft_strlen(src));
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

/*
 *	Function: fd_lstadd_front
 *	------------------------
 *	Adds a node to the beginning of an fd list, making it the new head
 *	lst: Pointer to the head of the list
 *	new: Node to be added to the list
 */
void	fd_lstadd_front(t_fd_map **lst, t_fd_map *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}
