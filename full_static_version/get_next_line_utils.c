/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:37:38 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/19 22:28:04 by sydauria         ###   ########.fr       */
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

void	*free_those(void *ptr1, void *ptr2)
{
	if (ptr1)
		free(ptr1);
	ptr1 = NULL;
	if (ptr2)
		free(ptr2);
	return (ptr1);
}

void	ft_strcpy(char *buff, char *tab)
{
	int i;

	i = 0;
	if (!buff || !tab)
		return;
	while (tab[i])
	{
		buff[i] = tab[i];
		i++;
	}
	buff[i] = '\0';
}

char	*check_read(int to_check, char *to_free)
{
	if (to_check < 0)
		return (free_those(to_free, to_free));
	return (to_free);
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
		return (free_those(s1, s2));
	if (s1)
	{
		while (s1[i])
			s3[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	free_those(s1, s2);
	return (s3);
}
