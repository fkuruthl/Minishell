/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:53:48 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:35:17 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_cd_args(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[i])
		i++;
	return (i - 1);
}

int	bool_key_match(char *s1, char *s2)
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

char	*copy_new_environ(char *env_var, char *new_val)
{
	char	*buffer;
	int		i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	buffer = (char *)malloc(i + 1 + ft_strlen(new_val) + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (env_var[i] && env_var[i] != '=')
	{
		buffer[i] = env_var[i];
		i++;
	}
	buffer[i++] = '=';
	ft_strlcpy(buffer + i, new_val, ft_strlen(new_val) + 1);
	free(env_var);
	return (buffer);
}

static char	**add_old_pwd(char **env_list, char *new_val)
{
	char	**buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env_list[i])
		i++;
	buffer = (char **)malloc(sizeof(char *) * (i + 1 + 1));
	i = 0;
	while (env_list[i])
	{
		buffer[j++] = ft_strdup(env_list[i]);
		free(env_list[i++]);
	}
	buffer[j] = (char *)malloc(ft_strlen("OLDPWD")
			+ ft_strlen(new_val) + 2);
	ft_strlcpy(buffer[j], "OLDPWD", 7);
	buffer[j][6] = '=';
	ft_strlcpy(buffer[j++] + 7, new_val, ft_strlen(new_val) + 1);
	buffer[j] = NULL;
	return (free(env_list), buffer);
}

char	**update_env_list(char **env_list, char *var, char *new_val)
{
	char	**buffer;
	int		i;

	buffer = env_list;
	if (!env_list || !var || !new_val)
		return (buffer);
	i = 0;
	while (env_list[i])
	{
		if (bool_key_match(env_list[i], var))
			break ;
		i++;
	}
	if (!env_list[i] && !ft_strncmp(var, "OLDPWD", ft_strlen(var)))
	{
		buffer = add_old_pwd(env_list, new_val);
		return (buffer);
	}
	if (!env_list[i])
		return (buffer);
	env_list[i] = copy_new_environ(env_list[i], new_val);
	return (buffer);
}
