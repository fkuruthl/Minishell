/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:19:07 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 10:50:43 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path_list(t_minishell *shell)
{
	char	**buffer;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp("PATH", shell->env[i++], 4))
			break ;
	}
	if (shell->env[i] == NULL)
		return (NULL);
	i--;
	buffer = ft_split(shell->env[i] + 5, ':');
	i = 0;
	while (buffer[i])
	{
		buffer[i] = ft_strjoin(buffer[i], "/");
		i++;
	}
	return (buffer);
}

char	*check_access(t_minishell *shell, t_command *cmd)
{
	int		i;
	char	**path_list;
	char	*full_path;

	i = 0;
	path_list = get_path_list(shell);
	if (!path_list)
		return (NULL);
	full_path = NULL;
	while (path_list[i])
	{
		full_path = ft_strjoin(path_list[i++], cmd->cmd_path);
		if (access(full_path, F_OK) == -1)
		{
			free(full_path);
			full_path = NULL;
		}
		else
			break ;
	}
	while (path_list[i])
		free(path_list[i++]);
	free(path_list);
	return (full_path);
}

void	set_up_command(t_ASTree *node, t_minishell *shell, t_command *cmd)
{
	int	arg_count;

	arg_count = count_cmd_args(node, shell);
	cmd->cmd_args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->cmd_args)
	{
		warn_message();
		return ;
	}
	set_up_cmd_members(node, shell, cmd);
}

void	print_cmd_args(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[i])
		printf("%s\n", cmd->cmd_args[i++]);
}
