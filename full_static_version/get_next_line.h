/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:18:23 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/21 17:29:50 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

void	ft_strcpy(char *buff, char *tab);
char	*fill_line(char *buffer, int *n);
char	*ft_memmove(char *dest, char *src);
char	*check_read(int to_check, char *to_free);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*core(int fd, char *buff, char *str);
void	*free_those(void *ptr1, void *ptr2);
size_t	ft_strlen(char *str);

#endif
