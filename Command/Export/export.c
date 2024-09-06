/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:15:54 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:36:36 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export(t_minishell *shell, t_command *cmd)
{
	shell->exit_status = 0;
	if (cmd->stdin_pipe == 1 || cmd->stdout_pipe == 1)
		return (shell->exit_status);
	if (cmd->cmd_args[1])
		export_w_flags(shell, cmd);
	else
		export_no_flags(shell);
	return (shell->exit_status);
}
