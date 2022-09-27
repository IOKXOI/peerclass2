/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:37:38 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/07 18:38:25 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*free_this(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (ptr);
}

int	check_problems(void *ptr, t_Lines *first)
{
	if (!ptr)
	{
		while (first)
		{
			list_delone(ptr, first);
			first = first->next;
		}
		return (1);
	}
	return (0);
}

char	*list_delone(t_Lines *list, t_Lines **first)
{
	char	*str;

	str = NULL;
	(void)first;
	if (list->line)
	{
		str = list->line;
		free_this(list->line);
	}
	if (list->next && !list->prev)
	{
		list->next->prev = NULL;
		*first = list->next;
	}
	else if (list->prev && !list->next)
		list->prev->next = NULL;
	else if (list->next && list->prev)
	{
		list->prev->next = list->next;
		list->next->prev = list->prev;
	}
	else
	{
		*first = free_this(list);
		return (str);
	}
	return (free_this(list), str);
	
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	if (s1)
	{
		while (s1[i])
			s3[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	if (s1)
		free_this(s1);
	if (s2)
		free_this(s2);
	return (s3);
}
