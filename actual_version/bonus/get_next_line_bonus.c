/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:04:39 by sydauria          #+#    #+#             */
/*   Updated: 2022/04/04 00:31:29 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
/*
Fonction permettant d'allouer dynamiquement de l'espace pour le buffer. J'ai choisis de ne pas creer un char *buffer, mais de me servir de mon char **
	pour stocker mon buffer. J'avais un choix a faire parmit mes 6 variables, et c'est elle que j'ai choisis de car les autres me semble essentielles,
	et celle-ci reste un buffer que je stock dans un tableau qui stock des buffers.
*/

static ssize_t	create_and_fill_buffer(int fd, char **buffer)
{
	ssize_t	nb;

	buffer[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer[fd])
		return (-1);
	nb = read(fd, buffer[fd], BUFFER_SIZE);
	if (nb < 1)
		return (nb);
	buffer[fd][nb] = '\0';
	return (nb);
}

/*
Cette fonction me sert a savoir si je m'arrete a cause d'une erreur, ou si c'est la fin de fichier. 
	Je peux donc adapter mes frees et mes returns. J'avais d'abord programme ces instructions dans create_and_fill_buffer,
	pour m'eviter de declarer un int nb dans get_next_line, et pour eviter d'utiliser un char ** pour referencer la nouvelle adresse a buff. 
	Je me suis ensuite dit que c'etait mieux de separer la creation et le remplissage du buffer de la verification des conditions. Bon choix??
	(ne pas avoir de int nb me permettrait d'avoir un buffer en dehors de mon tableau, mais me semble moins adapte).
*/
static char	*stop_condition(int fd, ssize_t nb, char *valid_line, char **buffer)
{
	if (nb < 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		if (valid_line)
			free(valid_line);
		return (NULL);
	}
	if (nb == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (valid_line);
}

/*
Cette fonction me sert a recuperer ce que j'ai stocker dans le buffer, jusqu'au '\n' s'il est present, ou jusqu'au '\0'. 
	Lorsque je copie un '\n', je passe new_line a TRUE, pour indiquer au programme d'arreter de boucler. Ca m'evite d'iterer une autre fois,
	sur la meme string, a la recherche du meme caractere. Mais ca me coute une variable et une ligne de definition. UNe fois la string extraite du buffer,
	je memoove, pour garder uniquement la partie non utilise de mon buffer.
*/
static char	*extract_str(char *buffer, ssize_t *new_line)
{
	char	*extracted;
	size_t	i;

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

/*
J'utilise cette fonction pour mettre a null mon buffer si j'ai extrait l'integralite du buffer ou return un nouveau buffer avec le reste non utilise.
	Ca me permet de remplir la condition pour creer un nouveau buffer lors du prochain read.
	Je ne sais pas si le strndup est pertinent. C'est pour ne pas garder de la memoire alloue non utile, mais ca demande une nouvelle allocation.
*/
static char	*get_remainder(ssize_t *problem, ssize_t *exit_loop, char *buffer)
{
	char	*new_remainder;

	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	new_remainder = ft_strndup(buffer, BUFFER_SIZE); //oblige de ndup je peux pas faire un strdup classique j'ai plus de fonction dispo
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
	static char	*buffer[1024];
	ssize_t		nb;
	ssize_t		new_line;

	new_line = FALSE;
	valid_line = NULL; //Je dois initialiser valid_line a NULL, car si un probleme survient 
					   //lors du read, je dois la free si elle est alloue, mais dans le cas ou
					   //un probleme survient lors du premier appel de create_and_fill_buffer
					   //je dois l'avoir initialiser avant de l'utiliser. En plus ma fonction 
					   //return NULL dans le cas de la fin de fichier ou dans le cas d'un probleme.
					   //Je n'ai donc pas moyen de savoir la raison du return NULL. Donc, je return 
					   //valid_line dans tout les cas, si le NULL est cause par une erreur.
	nb = 2; //nb initialise a 2 pour ne pas rentrer dans de mauvaises conditions dans stop_condition,
			//dans le cas ou je ne re-read pas, car j'ai deja un buffer avec du contenu a exploiter. ( je vois pas comment faire ca propre).
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (free_all_fd(buffer));
	while (!new_line)
	{
		if (!buffer[fd])
			nb = create_and_fill_buffer(fd, buffer);
		if (nb < 1)
			return (stop_condition(fd, nb, valid_line, buffer));
		temp = extract_str(buffer[fd], &new_line); //j'extrait ma chaine jusqu'au \n s'il y a, sinon jusqu'a fin de buffer. Si allocation echoue, str_join va return NULL;
		valid_line = ft_strjoin_and_free(valid_line, temp); //si j'ai une valid_line, je lui join la str temp fraichement extraite. Sinon, je recupere juste temp dans valid line.
															//j'ai choisis de free temp dans le join pour eviter de refaire une allocation dynamique  inutile dans le cas ou je n'ai pas de valid_line.
		if (!valid_line)
			return (stop_condition(fd, -1, valid_line, buffer));
		buffer[fd] = get_remainder(&nb, &new_line, buffer[fd]);
	}
	return (stop_condition(fd, nb, valid_line, buffer));
}

