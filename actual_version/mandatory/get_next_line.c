/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:24:06 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/25 06:22:45 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s3)
	{
		if (s1)
		{
			while (s1[i])
				s3[j++] = s1[i++];
		}
		free_this(&s1);
		i = 0;
		while (s2[i])
			s3[j++] = s2[i++];
		free_this(&s2);
		s3[j] = '\0';
		return (s3);
	}
	free_this(&s1);
	return(free_this(&s2));
}

char *check_read(char **index, int fd, int nb)
{
	if (nb < 1)
	{
		if (nb < 0)
			return (free_all(index));
		index[fd] = free_this(&index[fd]);
	}
	return (index[STR_TO_RETURN]);
}

char	*get_remainder(char *buffer, int *status)
{
	char	*remainder;

	remainder = NULL;
	if (buffer)
		remainder = ft_strndup(buffer, BUFFER_SIZE);
	if (!remainder)
		*status = 2;
	if (*remainder == '\0')
		return (free_this(&remainder));
	return(remainder);
}


char	*extract_buffer(char **index, char *buffer, int *status)
{
	int		i;
	char	*extracted;
	char	*to_join;

	index[STR_TO_RETURN] = NULL;
	i = 0;
	while (buffer[i + 1] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		*status = 1;
	extracted = ft_strndup(buffer, i);
	if (extracted)
	{
		ft_memmove(&buffer[0], &buffer[i + 1]);
		to_join = index[STR_TO_RETURN];
		index[STR_TO_RETURN] = ft_strjoin(to_join, extracted);
		if (index[STR_TO_RETURN])
			return (index[STR_TO_RETURN]);
	}
	*status = 2;
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			nb;
	int			status;
	static char *index[FD_LIMIT+1];
	char		buffer[BUFFER_SIZE + 1];

	status = 0;
	index[STR_TO_RETURN] = '\0';
	if (fd < 0 || fd > FD_LIMIT || BUFFER_SIZE < 1)
		return (free_all(index));
	while (!status)
	{
		if (!index[fd])
		{
			nb = read(fd, buffer, BUFFER_SIZE);
			if (nb < 1)
				return (check_read(index, fd, nb));
			buffer[nb] = '\0';
		}
		index[STR_TO_RETURN] = extract_buffer(index, buffer, &status);
		if(status == 2)
			return(free_all(index));
		index[fd] = get_remainder(buffer, &status);
//		if (!*index[fd])
//			free
		if (status == 2)
			return (free_all(index));
	}
	return (check_read(index, fd, nb));
}
