/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:17:01 by kalmheir          #+#    #+#             */
/*   Updated: 2022/02/21 07:58:53 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
 *	Function: fd_lstnew
 *	------------------------
 *	Allocates a new node for the fd list
 *	Returns: Pointer to the allocated node
 *	fd: Pointer to the file descriptor to be added
 *	buffer: Pointer to the new buffer created
 */
t_fd_map	*fd_lstnew(int *fd)
{
	t_fd_map	*result;
	char		*buff;
	int			i;

	i = 0;
	result = malloc(sizeof(t_fd_map));
	if (!result)
		return (0);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	while (i < BUFFER_SIZE + 1)
		buff[i++] = 0;
	result->buffer = buff;
	result->next = 0;
	result->prev = 0;
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
t_fd_map	*fd_lstget(t_fd_map **fd_list, int fd)
{
	t_fd_map	*tracer;

	if (!fd_list)
		return (0);
	tracer = *fd_list;
	while (tracer != 0 && *(tracer->fd) != fd)
		tracer = tracer->next;
	if (tracer && *(tracer->fd) != fd)
		return (0);
	return (tracer);
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
char	*ft_substr_unsafe(char *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;

	i = 0;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	while (i < len)
	{
		result[i] = s[i + start];
		i++;
	}
	result[len] = 0;
	return (result);
}

/*
 *	Function: ft_lstdelone
 *	------------------------
 *	Clears out an FD node
 *	lst: Node to delete
 */
void	fd_lstdelone(t_fd_map *lst)
{
	if (lst->next && lst->prev)
	{
		(lst->next)->prev = lst->prev;
		(lst->prev)->next = lst->next;
	}
	free(lst->buffer);
	lst->buffer = NULL;
	free(lst);
}

/*
 *	Function: ft_strchr
 *	------------------------
 *	Locates the first occurence of a character in a string
 *	Returns: pointer to the located character, or NULL if not found
 *	s: String to search through
 *	c: Character to search for
 */
char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (!c)
		return ((char *)(s + i));
	return (0);
}
