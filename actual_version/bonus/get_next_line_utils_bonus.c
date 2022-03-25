/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:37:38 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/25 11:21:08 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_memmove(char *dest, char *src)
{
	size_t	i;
	
	i = 0;
	if (src)
	{
		while(src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
}


char	*free_this(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	return (NULL);
}

void	*free_all(char **remainder)
{
	int	i;

	i = 0;
	if (remainder)
	{
		while (i < FD_LIMIT)
		{
			free_this(&remainder[i]);
			remainder[i] = NULL;
			i++;
		}

	}
	return (NULL);
}

char	*ft_strndup(char *buffer, int n)
{
	int		i;
	char	*str;
	
	i = 0;
	str = NULL;
	if (buffer)
	{
		str = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
		if (str)
		{
			while (buffer[i] && i <= n)
			{
				str[i] = buffer[i];
				i++;
			}
			str[i] = '\0';
		}
//		free_this(&buffer);
	}
	return (str);
}

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
