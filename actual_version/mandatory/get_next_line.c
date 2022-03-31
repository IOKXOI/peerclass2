/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:04:39 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/31 07:44:22 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	create_and_fill_buffer(int fd, char *buffer)
{
	ssize_t	nb;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	nb = read(fd, buffer, BUFFER_SIZE);
	if (nb < 1)
		return (nb);
	buffer[nb] = '\0';
	return (nb);
}

char	*stop_condition(int nb, char *valid_line, char *buffer)
{
	if (nb < 0)
	{
		free(buffer);
		if (valid_line)
			free(valid_line);
		return (NULL);
	}
	if (nb == 0)
		free(buffer);
	return (valid_line);
}

char	*extract_str(char *buffer, ssize_t *new_line)
{
	size_t	i;
	char	*extracted;

	i = 0;
	while (*(buffer + (i + 1)) && *(buffer + i) != '\n')
		i++;
	if (*(buffer + i) == '\n')
		*new_line = TRUE;
	extracted = ft_strndup(buffer, i);
	if (!extracted)
		return (NULL);
	ft_memmove(buffer, (buffer + (i + 1)), ft_strlen((buffer + i)));
	return (extracted);
}

char	*get_remainder(ssize_t *problem, ssize_t *exit_loop, char *buffer)
{
	char	*new_remainder;

	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	new_remainder = ft_strdup(buffer);
	if (!new_remainder)
	{
		*problem = -1;
		*exit_loop = TRUE;
		return (NULL);
	}
	free(buffer);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	char		*valid_line;
	char		*temp;
	static char	*buffer;
	ssize_t		nb;
	ssize_t		new_line;

	valid_line = NULL;
	nb = 2;
	new_line = FALSE;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	while (!new_line)
	{
		if (!buffer)
			nb = create_and_fill_buffer(fd, buffer);
		if (nb < 1)
			return (stop_condition(nb, valid_line, buffer));
		temp = extract_str(buffer, &new_line);
		valid_line = ft_strjoin_and_free(valid_line, temp);
		if (!valid_line)
			return (stop_condition(-1, valid_line, buffer));
		buffer = get_remainder(&nb, &new_line, buffer);
	}
	return (stop_condition(nb, valid_line, buffer));
}
