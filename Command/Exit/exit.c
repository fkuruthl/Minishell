/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:51:22 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:35:52 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_multi_arg(t_command *cmd)
{
	if (bool_numeric(cmd->cmd_args[1]))
	{
		ft_dprintf(2, "-minishell: exit: too many arguments\n");
		return (1);
	}
	else
	{
		ft_dprintf(2, "-minishell: exit: %s: numeric argument required\n",
			cmd->cmd_args[1]);
		return (2);
	}
}

static int	handle_one_arg(t_command *cmd)
{
	if (bool_numeric(cmd->cmd_args[1]))
		return ((unsigned char) ft_atoi(cmd->cmd_args[1]));
	else
	{
		ft_dprintf(2, "-minishell: exit: %s: numeric argument required\n",
			cmd->cmd_args[1]);
		return (2);
	}
}

int	ft_exit(t_minishell *shell, t_command *cmd)
{
	unsigned char	status;
	int				arg_count;

	arg_count = count_exit_args(cmd);
	status = 0;
	ft_dprintf(1, "exit\n");
	if (arg_count > 1)
	{
		status = handle_multi_arg(cmd);
		if (status == 1)
		{
			shell->exit_status = status;
			return (status);
		}
	}
	else if (arg_count == 1)
		status = handle_one_arg(cmd);
	return (shell->exit_status = status, full_free(shell, cmd),
		exit(status), status);
}
