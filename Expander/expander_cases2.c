/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cases2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:27:10 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_diff_len(char *env)
{
	int	sub_len;
	int	add_len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] && (env[i] != '='))
		i++;
	sub_len = i + 1;
	i++;
	while (env[i + j])
		j++;
	add_len = j;
	return (add_len - sub_len);
}

char	*detector(char *str, int s_ind, char *env[])
{
	char	*buffer;
	int		i;
	int		diff_len;

	i = 0;
	while (env[i])
	{
		if (in_env_string(str + s_ind, env[i]))
		{
			diff_len = get_diff_len(env[i]);
			buffer = (char *)malloc(ft_strlen(str) + (diff_len) + 1);
			if (!buffer)
				return (warn_message(), NULL);
			copier(buffer, str, env[i]);
			return (buffer);
		}
		i++;
	}
	return (NULL);
}
