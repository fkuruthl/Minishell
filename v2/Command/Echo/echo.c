/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:14:49 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 10:11:55 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_minishell *shell, t_command *cmd)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (cmd->cmd_args[i] && cmd->cmd_args[i][0]
		&& !ft_strncmp("-n", cmd->cmd_args[i],
			ft_strlen(cmd->cmd_args[i])))
	{
		flag = 1;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		ft_dprintf(1, "%s", cmd->cmd_args[i]);
		if (cmd->cmd_args[i + 1])
			ft_dprintf(1, " ");
		i++;
	}
	if (!flag)
		ft_dprintf(1, "\n");
	return (shell->exit_status = 0, 0);
}
