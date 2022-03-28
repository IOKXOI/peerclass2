/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_apprenti_jedi_version.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:50:32 by sydauria          #+#    #+#             */
/*   Updated: 2022/03/28 10:09:22 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GNL_APPRENTI_JEDI_VERSION_H
# define _GNL_APPRENTI_JEDI_VERSION_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

void	ft_memmove(void *dest, void *src);
char	*stop_condition(int nb, int fd, char *valid_line, char **buffer);
char	*extract_str(char *buffer, ssize_t *new_line);
char	*get_remainder(int *problem, int *exit_loop, char *buffer);
char	*get_next_line(int fd);
char	*ft_strjoin_and_free(char *actual_line, char *temp);
void	*free_all_fd(char **remainders);
char	*ft_strndup(char *buffer, int n);
size_t	ft_strlen(char *str);
ssize_t	*create_and_fill_buffer(int fd, char **buffer);

# endif
