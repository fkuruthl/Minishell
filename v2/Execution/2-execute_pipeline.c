/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-execute_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:40:25 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:32:30 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_node(t_ASTree *node, t_minishell *shell, t_command *cmd)
{
	int	stat_flag;

	stat_flag = 1;
	if (node->type == NODE_RDRGEN)
	{
		if (redir_handling(node, shell, cmd))
		{
			if (node->left)
			{
				set_up_command(node->left, shell, cmd);
				stat_flag = exec_smpl_command(shell, cmd);
			}
		}
		else
		{
			stat_flag = 0;
			cmd->pids[(cmd->pid_i)++] = -2;
		}
	}
	else if (node->type == NODE_CMDPATH)
	{
		set_up_command(node, shell, cmd);
		stat_flag = exec_smpl_command(shell, cmd);
	}
	return (stat_flag);
}

static void	pipe_chain_exec(t_ASTree **tree, t_command *cmd,
								t_minishell *shell, int *fd)
{
	while ((*tree)->right->type == NODE_PIPE)
	{
		*tree = (*tree)->right;
		init_pipe_command(cmd);
		close(cmd->pipewrite);
		cmd->stdin_pipe = 1;
		cmd->stdout_pipe = 1;
		do_pipe(shell, cmd, fd);
		cmd->copy_rd_fd = fd[0];
		cmd->pipewrite = fd[1];
		exec_node((*tree)->left, shell, cmd);
		close(cmd->piperead);
		cmd->piperead = fd[0];
		delete_pipe_command(cmd);
	}
}

void	execute_pipeline(t_minishell *shell, t_command *cmd, int proc_count)
{
	int			fd[2];
	t_ASTree	*tree;
	int			stat_flag;

	do_pipe(shell, cmd, fd);
	tree = shell->ast;
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!init_command(cmd, proc_count))
		return ;
	cmd->piperead = fd[0];
	cmd->pipewrite = fd[1];
	cmd->copy_rd_fd = fd[0];
	cmd->stdin_pipe = 0;
	cmd->stdout_pipe = 1;
	exec_node(tree->left, shell, cmd);
	delete_pipe_command(cmd);
	pipe_chain_exec(&tree, cmd, shell, fd);
	init_pipe_command(cmd);
	close(cmd->pipewrite);
	cmd->stdin_pipe = 1;
	cmd->stdout_pipe = 0;
	stat_flag = exec_node(tree->right, shell, cmd);
	close(cmd->piperead);
	waiter(shell, cmd, proc_count, stat_flag);
	delete_command(cmd);
}
