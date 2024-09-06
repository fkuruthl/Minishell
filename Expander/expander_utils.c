/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:27:10 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trailor_validity(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (c == '_')
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (0);
}

int	choose_state2(char c, int state)
{
	if (c == '\'' && state == STATE_GENERAL)
		return (IN_SQUOTE);
	else if (c == '\'' && state == IN_SQUOTE)
		return (STATE_GENERAL);
	if (c == '"' && state == STATE_GENERAL)
		return (IN_DQUOTE);
	else if (c == '"' && state == IN_DQUOTE)
		return (STATE_GENERAL);
	return (state);
}

int	in_env_string(char *str1, char *env_str)
{
	int	j;

	j = 0;
	while ((env_str[j] != '=') && (str1[j] == env_str[j])
		&& str1[j] && env_str[j])
		j++;
	if (env_str[j] == '=')
		return (j);
	return (0);
}

static void	copy_expansion(char *buffer, char *str, char *env)
{
	int	k;
	int	i;
	int	j;

	k = 0;
	i = 0;
	j = 0;
	while (env[k] != '=')
		k++;
	k++;
	while (env[k])
		buffer[j++] = env[k++];
	i += 2;
	while (trailor_validity(str[i]))
		i++;
	while (str[i])
		buffer[j++] = str[i++];
	buffer[j] = '\0';
}

void	copier(char *buffer, char *str, char *env)
{
	int	i;
	int	j;
	int	state;

	i = 0;
	j = 0;
	state = STATE_GENERAL;
	while (str[i])
	{
		state = choose_state2(str[i], state);
		if (not_stand_alone(str[i], str[i + 1], state))
		{
			if (in_env_string(str + i + 1, env))
				break ;
		}
		buffer[j++] = str[i++];
	}
	copy_expansion(buffer + j, str + i, env);
}
