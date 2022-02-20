/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:17:04 by kalmheir          #+#    #+#             */
/*   Updated: 2022/02/21 02:46:35 by kalmheir         ###   ########.fr       */
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
char	*ft_strjoin2(char *str1, char *str2)
{
	int		strslen;
	char	*holder;

	strslen = ft_strlen(str1);
	strslen += ft_strlen(str2);
	holder = malloc(strslen + 1);
	if (!holder)
		return (0);
	*holder = 0;
	ft_strcat(holder, str1);
	ft_strcat(holder, str2);
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

/*
 *	Function: get_next_line
 *	------------------------
 *	Returns: a line read from a file descriptor
 *	fd: File descriptor to read from
 *	@TODO:
 *		1. if buffer not empty:
 *			a. join with result.
 *			b. if no new line; get new buffer go to 1a.
 *		2. Get new buffer, go to 1a.
 *		3. If buffer has new line; return output
 *	@NOTE:
 *		Double check and make sure everything except-
 *		return string and buffer are freed.
 */
char	*get_next_line(int fd)
{
	static t_fd_map	*fd_list;
	t_fd_map		*current;
	char			*result;

	result = malloc(BUFFER_SIZE);
	if (!result)
		return (0);
	if (!fd_list)
		fd_list = fd_lstnew(&fd, result);
	current = fd_lstget(fd_list, fd);
	if (!current)
	{
		fd_lstadd_front(&fd_list, fd_lstnew(&fd, result));
		current = fd_list;
		fd_list->buffer[0] = 0;
	}
	return (result);
}
