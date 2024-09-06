/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-execute_simple_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:43:39 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:32:53 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_built_ins(t_minishell *shell, t_command *cmd)
{
	cmd->pids[(cmd->pid_i)++] = -2;
	built_in_dup(cmd);
	call_built_ins(shell, cmd);
	dup2(cmd->save_stdout, STDOUT_FILENO);
	dup2(cmd->save_stdin, STDIN_FILENO);
}

int	exec_smpl_command(t_minishell *shell, t_command *cmd)
{
	if (!cmd->cmd_path)
		return (0);
	cmd->save_stdin = dup(STDIN_FILENO);
	cmd->save_stdout = dup(STDOUT_FILENO);
	if (check_built_ins(cmd))
		return (exec_built_ins(shell, cmd), 0);
	if (check_directory(shell, cmd))
		return (0);
	if (no_permissions(shell, cmd))
		return (0);
	init_child_signals();
	cmd->pids[cmd->pid_i] = fork();
	if (cmd->pids[cmd->pid_i] == -1)
	{
		perror("fork");
		ft_cleanup(shell, cmd);
		exit(1);
	}
	if (cmd->pids[(cmd->pid_i)++] != 0)
		return (1);
	regular_dup(cmd);
	if (execve(cmd->cmd_full_path, cmd->cmd_args, shell->env) == -1)
		handle_execve_error(shell, cmd);
	return (1);
}
