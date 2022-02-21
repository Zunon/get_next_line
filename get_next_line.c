/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:17:04 by kalmheir          #+#    #+#             */
/*   Updated: 2022/02/21 08:10:17 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 *	Function: ft_strlen
 *	------------------------
 *	Computes the length of a string, not including the terminating null
 *	Returns: length of the string
 *	str: The string to measure
 */
int	ft_strlen(char *str)
{
	int	n;

	n = -1;
	while (str[++n])
		;
	return (n);
}

/*
 *	Function: ft_strjoin2
 *	------------------------
 *	Appends a copy of a source string to the end of the destination string
 *	dest: Destination string
 *	src: Source string
 */
void	ft_strcat(char *dest, char *src)
{
	while (*dest++)
		;
	dest--;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
}

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
	int		strslen;
	char	*holder;

	if (!str1 || !str2)
		return (0);
	strslen = ft_strlen(str1);
	strslen += ft_strlen(str2);
	holder = malloc(strslen + 1);
	if (!holder)
		return (0);
	*holder = 0;
	ft_strcat(holder, str1);
	ft_strcat(holder, str2);
	free(str1);
	str1 = NULL;
	if (free2)
	{
		free(str2);
		str2 = NULL;
	}
	return (holder);
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
 *	Function: get_next_line
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
	size_t			len;
	int nullloc;

	if (fd < 0)
		return (0);
	if (!fd_list)
		fd_list = fd_lstnew(&fd);
	current = fd_lstget(fd_list, fd);
	if (!current)
	{
		fd_lstadd_front(&fd_list, &fd);
		current = fd_list;
	}
	if (!((current->buffer)[0]))
	{
		if (read(fd, current->buffer, BUFFER_SIZE) < 1)
		{
			current->buffer[0] = 0;
			if (current == fd_list)
			{
				if (current->next)
					fd_list = current->next;
				else
					fd_list = NULL;
			}
			fd_lstdelone(current);
			current = NULL;
			return (0);
		}
	}
	result = malloc(1);
	if (!result)
		return (0);
	result[0] = 0;
	newline = ft_strchr(current->buffer, '\n');
	while (!newline)
	{
		result = ft_strjoin2(result, current->buffer, 0);
		nullloc = read(fd, current->buffer, BUFFER_SIZE);
		if (nullloc < 1)
		{
			for (int i = 0; i < BUFFER_SIZE + 1; i++)
				(current->buffer)[i] = 0;
			if (current == fd_list)
			{
				if (current->next)
					fd_list = current->next;
				else
					fd_list = NULL;
			}
			fd_lstdelone(current);
			current = NULL;
			return (result);
		}
		(current->buffer)[nullloc] = 0;
		newline = ft_strchr(current->buffer, '\n');
	}
	if (newline == (current->buffer) + BUFFER_SIZE - 1)
	{
		result = ft_strjoin2(result, (current->buffer), 0);
		for (int i = 0; i < BUFFER_SIZE + 1; i++)
			(current->buffer)[i] = 0;
		return (result);
	}
	len = newline - current->buffer;
	result = ft_strjoin2(result, ft_substr(current->buffer, 0, len + 1), 1);
	newline = ft_substr(newline, 1, ft_strlen(newline + 1));
	ft_strlcpy(current->buffer, newline, BUFFER_SIZE + 1);
	free(newline);
	newline = NULL;
	return (result);
}
