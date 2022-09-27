/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:16:58 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/25 17:27:00 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define FD_MAX 256

char	*fill_line(char *buffer, int *n)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = NULL;
	while (buffer[i + 1] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		*n = 1;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	str[i + 1] = '\0';
	while (j <= i)
	{
		str[j] = buffer[j];
		j++;
	}
	if (buffer[j])
		ft_memmove(&buffer[0], &buffer[j]);
	else
		ft_memmove(&buffer[0], &buffer[0]);
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
		if (src[i])
		{
			while(src[i])
			{
				dest[i] = src[i];
				i++;
			}
		}
		while (i < BUFFER_SIZE)
			dest[i++] = '\0';
	}
	return (dest);
}



char *core(int fd, char *buff, char *str)
{
	char 	*temp;
	int		n;
	
	temp = NULL;
	n = 0;
	while (!n)
	{
		if (!buff[0])
		{
			n = read(fd, buff, BUFFER_SIZE);
			if (n < 1)
				return(check_read(n, str));
			buff[n] = '\0';
		}
		n = 0;
		temp = fill_line(buff, &n);
		if (!temp)
			return (free_those(str, str));
		str = ft_strjoin(str, temp);
		if (!str)
			return (free_those(str, temp));
	}
	return (str);
}


char	*get_next_line(int fd)
{
	static char	tab[FD_MAX][BUFFER_SIZE + 1];
	char		*str;

	str = NULL;
	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE < 1)
		return (NULL);
	str = core(fd, tab[fd], str);
	return (str);
}
