/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:24:06 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/25 14:49:47 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

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

char	*save_buffer(char *buffer, int *status)
{
	char	*save;

	save = NULL;
	if (buffer)
		save = ft_strndup(buffer, BUFFER_SIZE);
	if (!save)
		*status = 2;
	if (*save == '\0' ||ft_strlen(save) < 1)
		return (free_this(&save));
	return(save);
}


char	*extract_str(char **index, char *buff, int fd, int *status)
{
	int		i;
	char	*extracted;
	char	*to_join;
	i = 0;
	
	while (buff[i + 1] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		*status = 1;
	extracted = ft_strndup(buff, i);
	if (extracted)
	{
		ft_memmove(&buff[0], &buff[i + 1]);
		if (ft_strlen(buff) < 1)
			index[fd] = free_this(&buff);
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
	static char *index[FD_LIMIT];

	nb = 2;
	status = 0;
	index[STR_TO_RETURN] = NULL;
	if (fd < 0 || fd > FD_LIMIT || BUFFER_SIZE < 1)
		return (free_all(index));
	while (!status)
	{
		if (!index[fd] || ft_strlen(index[fd]) < 1)
		{
			index[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
			if (!index[fd])
				return(free_all(index));
			nb = read(fd, index[fd], BUFFER_SIZE);
			//printf("NB = %d\n",nb);
			if (nb < 1)
				return (check_read(index, fd, nb));
			index[fd][nb] = '\0';
		}
	//	printf("str = %s\nfd = %d\n nb =%d\n",index[fd],fd,nb);
		index[STR_TO_RETURN] = extract_str(index, index[fd], fd, &status);
		if (status == 2)
			return (free_all(index));
	}
	index[STR_TO_RETURN] = check_read(index, fd, nb);
	return (index[STR_TO_RETURN]);
}		
