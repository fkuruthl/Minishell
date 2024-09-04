/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:13:23 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:18:40 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	bool_uns_key_match(char *s1, char *s2)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (char *)malloc(ft_strlen(s1) + 1);
	while (s1[i])
	{
		if (s1[i] == '=')
			break ;
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	if (!ft_strncmp(temp, s2, ft_strlen(s2) + 1))
		return (free(temp), 1);
	return (free(temp), 0);
}

static int	is_key_match(char **env_list, char *str)
{
	int	i;

	i = 0;
	while (env_list[i])
	{
		if (bool_uns_key_match(env_list[i], str))
			return (1);
		i++;
	}
	return (0);
}

static char	**rmv_from_list(char **env_list, char *str)
{
	char	**buffer;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	buffer = NULL;
	while (env_list[i])
		i++;
	buffer = (char **)malloc(sizeof(char *) * (i - 1 + 1));
	i = 0;
	while (env_list[i])
	{
		if (!bool_uns_key_match(env_list[i], str))
		{
			len = ft_strlen(env_list[i]);
			buffer[j] = (char *)malloc(len + 1);
			ft_strlcpy(buffer[j++], env_list[i], len + 1);
		}
		free(env_list[i]);
		i++;
	}
	buffer[j] = NULL;
	return (free(env_list), buffer);
}

static int	valid_syntax(char *str)
{
	int	i;

	i = 0;
	if (!(str[i] == '_' || ft_isalpha(str[i])))
		return (0);
	i++;
	while (str[i])
	{
		if (!(str[i] == '_' || ft_isalnum(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_minishell *shell, t_command *cmd)
{
	int		i;

	i = 1;
	shell->exit_status = 0;
	while (cmd->cmd_args[i])
	{
		if (valid_syntax(cmd->cmd_args[i]))
		{
			if (is_key_match(shell->env, cmd->cmd_args[i]))
				shell->env = rmv_from_list(shell->env, cmd->cmd_args[i]);
		}
		else
		{
			ft_dprintf(2, "-minishell: unset: '%s': not a valid identifier\n",
				cmd->cmd_args[i]);
			shell->exit_status = 1;
		}
		i++;
	}
	return (shell->exit_status);
}
