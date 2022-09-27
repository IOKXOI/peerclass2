/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:16:58 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/08 15:35:50 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_Lines	*where_is_my_node(int fd, t_Lines *first)
{
	t_Lines	*list;

	list = first; 
	if (list)
	{
		while (list && list->id != fd)
			list = list->next;
		if (list && list->id == fd)
		{
			list->line = NULL;
			list->status_line = 0;
			return (list);
		}
	}
	return (list);
}

t_Lines	*create_node(int fd, t_Lines *first)
{
	t_Lines	*new_link;
	
	new_link = malloc(sizeof(t_Lines));
	if (!new_link)
		return (NULL);
	new_link->prev = NULL;
	new_link->id = fd;
	new_link->status_line = 0;
	new_link->status_buffer = 0;
	new_link->line = NULL;
	ft_memmove(new_link->buffer, new_link->buffer);
	if (first == NULL)
		new_link->next = NULL;
	else
	{
		new_link->next = first;
		first->prev = new_link;
	}
	return (new_link);
}

char	*fill_line(t_Lines *list)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	str = NULL;
	while (list->buffer[i] && list->buffer[i] != '\n')
		i++;	
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	str[i + 1] = '\0';
	while (++j <= i)
		str[j] = list->buffer[j];
	if (str[i] == '\n')
		list->status_line = 1;
	ft_memmove(&list->buffer[0], &list->buffer[j]);
	if (list->buffer[0] == '\0')
		list->status_buffer = 0;
	return (str);
}

char	*ft_memmove(char *dest, char *src)
{
	size_t	i;
	
	i = 0;
	if (dest == src)
	{
		while (i <= BUFFER_SIZE)
			dest[i++] = '\0';
	}
	else
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
	}
	while (i <= BUFFER_SIZE)
		dest[i++] = '\0';
	return (dest);
}




char	*get_next_line(int fd)
{
	t_Lines			*list;
	static t_Lines	*first = NULL;
	char			*str;

	if (fd < 1)
		return (NULL);
	list = where_is_my_node(fd, &first);
	if (!list)
		first = create_node();
	if (check_problems(list, first))
			return (NULL);
	while (list->status_line != 1)
	{
		if (list->status_buffer == 0)
		{
			if (read(fd, list->buffer, BUFFER_SIZE) < 1)
				return (list_delone(list, &first));
			list->status_buffer = 1;
		}
		str = fill_line(list);
		list->line = ft_strjoin(list->line, str);
		if (check_problems(list->line, first) || check_problems(str, first))
			return (NULL);
	}
	return (list->line);
}
