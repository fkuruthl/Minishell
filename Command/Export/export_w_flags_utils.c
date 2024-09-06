/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_w_flags_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:18:28 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:36:14 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_key(char *str)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = (char *)malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		buffer[i] = str[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

int	bool_same_key(char *s1, char *s2)
{
	char	*key1;
	char	*key2;

	key1 = extract_key(s1);
	key2 = extract_key(s2);
	if (!ft_strncmp(key1, key2, ft_strlen(key1) + 1))
		return (free(key1), free(key2), 1);
	return (free(key1), free(key2), 0);
}

char	*update_value(char *s1, char *s2)
{
	char	*buffer;
	int		i;

	i = 0;
	while (s2[i])
		i++;
	buffer = (char *)malloc(i + 1);
	ft_strlcpy(buffer, s2, i + 1);
	free(s1);
	return (buffer);
}

int	check_same_key(char **env_list, char *str)
{
	int	i;

	i = 0;
	while (env_list[i])
	{
		if (bool_same_key(env_list[i], str))
		{
			env_list[i] = update_value(env_list[i], str);
			return (1);
		}
		i++;
	}
	return (0);
}
