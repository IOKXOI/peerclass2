/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:50:32 by sydauria          #+#    #+#             */
/*   Updated: 2022/04/01 18:18:31 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define TRUE 1
# define FALSE 0

# include <stdlib.h>
# include <unistd.h>

void	*ft_memmove(void *dest, const void *src, size_t size);
char	*stop_condition(int fd, size_t nb, char *valid_line, char **buffer);
char	*extract_str(char *buffer, ssize_t *new_line);
char	*get_remainder(ssize_t *problem, ssize_t *exit_loop, char *buffer);
char	*get_next_line(int fd);
char	*ft_strjoin_and_free(char *actual_line, char *temp);
void	*free_all_fd(char **remainders);
char	*ft_strndup(char *buffer, int n);
size_t	ft_strlen(char *str);
ssize_t	create_and_fill_buffer(int fd, char **buffer);

#endif
