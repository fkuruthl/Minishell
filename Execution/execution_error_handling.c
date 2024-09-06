/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:30:40 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:33:00 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	bool_path_given(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] && str[i] != '/')
		i++;
	if (str[i])
		flag = 1;
	return (flag);
}

static int	check_executable_validity(t_minishell *shell, t_command *cmd)
{
	int	result;

	result = 0;
	if (!ft_strchr(cmd->cmd_full_path, '/'))
		return (result = 0, 0);
	if (access(cmd->cmd_full_path, F_OK) == 0)
	{
		if (access(cmd->cmd_full_path, X_OK) == -1)
		{
			ft_dprintf(2, "-minishell: %s: Permission denied\n",
				cmd->cmd_path);
			shell->exit_status = 126;
			result = 1;
		}
	}
	else
	{
		ft_dprintf(2, "-minishell: %s: No such file or directory\n",
			cmd->cmd_path);
		shell->exit_status = 127;
		result = 1;
	}
	return (result);
}

int	no_permissions(t_minishell *shell, t_command *cmd)
{
	int	result;

	result = 0;
	if (bool_path_given(cmd->cmd_path))
		cmd->cmd_full_path = ft_strdup(cmd->cmd_path);
	else
		cmd->cmd_full_path = check_access(shell, cmd);
	if (!(cmd->cmd_full_path))
		result = 0;
	result = check_executable_validity(shell, cmd);
	if (result == 1)
		cmd->pids[(cmd->pid_i)++] = -2;
	return (result);
}
