/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:17:04 by kalmheir          #+#    #+#             */
/*   Updated: 2022/03/15 00:34:20 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
 *	Function: ft_strjoin2
 *	------------------------
 *	Joins two strings into a newly allocated larger string
 *	Returns: pointer to the beginning of the allocated string
 *	str1: First string to join
 *	str2: Second string to join
 */
char	*ft_strjoin2(char *str1, char *str2, int free2)
{
	int		strlens[2];
	char	*holder;

	if (!str1 || !str2)
		return (0);
	strlens[0] = ft_strchr(str1, 0) - str1;
	strlens[1] = ft_strchr(str2, 0) - str2;
	holder = malloc(strlens[0] + strlens[1] + 1);
	if (!holder)
		return (0);
	*holder = 0;
	while (*str1)
		*holder++ = *str1++;
	while (*str2)
		*holder++ = *str2++;
	*holder = 0;
	free(str1 - strlens[0]);
	str1 = 0;
	if (free2)
	{
		free(str2 - strlens[1]);
		str2 = 0;
	}
	return (holder - strlens[0] - strlens[1]);
}

t_fd_map	*get_fd(int fd, t_fd_map **fd_list)
{
	t_fd_map	*current;

	if (!(*fd_list))
		*fd_list = fd_lstnew(&fd);
	current = fd_lstget(fd_list, fd);
	if (!current)
	{
		current = fd_lstnew(&fd);
		(*fd_list)->prev = current;
		current->next = *fd_list;
		*fd_list = current;
	}
	if (!((current->buffer)[0]))
	{
		if (read(fd, current->buffer, BUFFER_SIZE) < 1)
		{
			current->buffer[0] = 0;
			if (current == *fd_list)
				*fd_list = current->next;
			fd_lstdelone(current);
			current = NULL;
			return (0);
		}
	}
	return (current);
}

char	*returner(char *newline, t_fd_map **current, char *r)
{
	size_t	len;

	len = 0;
	if (newline == ((*current)->buffer) + BUFFER_SIZE - 1)
	{
		r = ft_strjoin2(r, ((*current)->buffer), 0);
		while (len <= BUFFER_SIZE)
			((*current)->buffer)[len++] = 0;
		return (r);
	}
	len = newline - (*current)->buffer;
	r = ft_strjoin2(r, ft_substr_unsafe((*current)->buffer, 0, len + 1), 1);
	newline = ft_substr_unsafe(newline, 1, ft_strchr(newline + 1, 0) - newline);
	len = 0;
	while (len < BUFFER_SIZE && newline[len])
	{
		((*current)->buffer)[len] = newline[len];
		len++;
	}
	((*current)->buffer)[len] = 0;
	free(newline);
	newline = NULL;
	return (r);
}

char	*end(t_fd_map **current, t_fd_map **fd_list, char **result)
{
	if (*current == *fd_list)
		*fd_list = (*current)->next;
	fd_lstdelone(*current);
	*current = 0;
	return (*result);
}

/*
 *	Function: get_next_line
 *	------------------------
 *	Returns: a line read from a file descriptor
 *	fd: File descriptor to read from
 *	@TODO:
 *		1. if buffer empty, get new buffer, go to 2.
 *		2. if no new line in buffer; join with result.
			otherwise go to 4.
 *		3. get new buffer, go to 2.
 *		4. If buffer has new line or we reached end; return output
 *	@NOTE:
 *		Double check and make sure everything except-
 *		return string and buffer are freed.
 */
char	*get_next_line(int fd)
{
	static t_fd_map	*fd_list;
	t_fd_map		*current;
	char			*result;
	char			*newline;
	int				nullloc;

	if (read(fd, 0, 0) < 0)
		return (0);
	current = get_fd(fd, &fd_list);
	result = malloc(1);
	if (!result || !current)
	{
		free(result);
		return (0);
	}
	result[0] = 0;
	newline = ft_strchr(current->buffer, '\n');
	while (!newline)
	{
		result = ft_strjoin2(result, current->buffer, 0);
		nullloc = read(fd, current->buffer, BUFFER_SIZE);
		if (nullloc < 1)
			return (end(&current, &fd_list, &result));
		(current->buffer)[nullloc] = 0;
		newline = ft_strchr(current->buffer, '\n');
	}
	return (returner(newline, &current, result));
}
