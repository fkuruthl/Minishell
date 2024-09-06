/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:57:42 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:34:10 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_key(char *str)
{
	char	*buffer;
	int		i;
	int		j;

	i = 1;
	while (str[i] && !ft_strchr("/", str[i]))
		i++;
	buffer = (char *)malloc(i + 1);
	if (!buffer)
		return (warn_message(), NULL);
	i = 1;
	j = 0;
	while (str[i] && !ft_strchr("/", str[i]))
		buffer[j++] = str[i++];
	buffer[j] = '\0';
	return (buffer);
}

int	check_ambiguous(t_minishell *shell, char *str)
{
	char	*key;
	int		i;
	int		j;

	key = NULL;
	i = 0;
	if (!str)
		return (0);
	if (str[0] != '$')
		return (0);
	key = ft_get_key(str);
	while (shell->env[i] && !bool_same_key(shell->env[i], key))
		i++;
	if (!(shell->env[i]))
		return (free(key), 0);
	j = 0;
	while (shell->env[i][j])
	{
		if (is_wspace(shell->env[i][j++]))
			return (free(key), 1);
	}
	return (free(key), 0);
}
