/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:13:39 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/06 20:28:48 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_to_path(char *path)
{
	char	*current_dir;
	char	*new_path;
	int		i;
	int		j;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_strdup(path));
	i = 0;
	new_path = malloc(ft_strlen(path) + ft_strlen(current_dir) + 2);
	if (!new_path)
		return (warn_message(), free(current_dir), ft_strdup(path));
	while (path[i])
	{
		new_path[i] = path[i];
		i++;
	}
	new_path[i++] = ':';
	j = 0;
	while (current_dir[j])
		new_path[i++] = current_dir[j++];
	new_path[i] = '\0';
	return (free(current_dir), new_path);
}

char	**setup_envlist(char *env[])
{
	int		i;
	char	**buffer;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	buffer = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			buffer[i] = append_to_path(env[i]);
		else
			buffer[i] = ft_strdup(env[i]);
		i++;
	}
	buffer[i] = NULL;
	return (buffer);
}

void	print_env_list(t_minishell minishell)
{
	int	i;

	i = 0;
	while (minishell.env[i])
		printf("%s\n", minishell.env[i++]);
	printf("\n");
}

void	delete_env_list(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!minishell->env)
		return ;
	while (minishell->env[i])
		free(minishell->env[i++]);
	free(minishell->env);
}
