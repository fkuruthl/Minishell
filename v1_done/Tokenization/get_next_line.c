/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:55 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:42:10 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nb_check(int nb_read, char *line, char *buffer)
{
	if (nb_read == -1)
	{
		if (line)
			free(line);
		return (free(buffer), 0);
	}
	if (nb_read == 0)
	{
		return (free(buffer), 1);
	}
	return (2);
}

// char	*get_next_line(int fd)
// {
// 	int		nb_read;
// 	char	*buffer;
// 	char	*line;
// 	int		nb_val;

// 	nb_read = -1;
// 	line = NULL;
// 	while (!ft_strchr(line, '\n') && nb_read != 0)
// 	{
// 		buffer = (char *) malloc(sizeof(*buffer) * (1 + 1));
// 		if (buffer == NULL)
// 		{
// 			if (line)
// 				free(line);
// 			return (NULL);
// 		}
// 		nb_read = read(fd, buffer, 1);
// 		nb_val = nb_check(nb_read, line, buffer);
// 		if (nb_val == 1)
// 			return (line);
// 		else if (nb_val == 0)
// 			return (NULL);
// 		buffer[nb_read] = '\0';
// 		line = ft_strjoin(line, buffer);
// 		free(buffer);
// 	}
// 	return (line);
// }
