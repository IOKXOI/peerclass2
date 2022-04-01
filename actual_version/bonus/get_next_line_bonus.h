/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:18:23 by sydauria          #+#    #+#             */
/*   Updated: 2022/04/01 18:20:33 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define TRUE 1
# define FALSE 0

# include <stdlib.h>
# include <unistd.h>

void	*ft_memmove(void *dest, const void *src, size_t size);
void	*free_all_fd(char **remainders);
char	*stop_condition(int fd, ssize_t nb, char *valid_line, char **buffer);
char	*extract_str(char *buffer, ssize_t *new_line);
char	*get_remainder(ssize_t *problem, ssize_t *exit_loop, char *buffer);
char	*get_next_line(int fd);
char	*ft_strjoin_and_free(char *actual_line, char *temp);
char	*ft_strndup(char *buffer, size_t n);
size_t	ft_strlen(char *str);
ssize_t	create_and_fill_buffer(int fd, char **buffer);

#endif
