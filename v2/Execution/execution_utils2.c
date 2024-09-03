/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:17:46 by hsalah             #+#    #+#             */
/*   Updated: 2024/08/02 09:24:00 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cleanup(t_minishell *shell, t_command *cmd)
{
	delete_command(cmd);
	delete_env_list(shell);
	delete_list(shell->tok_list);
	delete_binlist(shell->binlist);
	delete_node(shell->ast);
}

int	count_procs(t_ASTree *node)
{
	int			proc_count;

	proc_count = 0;
	while (node->type == NODE_PIPE)
	{
		proc_count++;
		node = node->right;
	}
	return (proc_count + 1);
}

void	do_pipe(t_minishell *shell, t_command *cmd, int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		ft_cleanup(shell, cmd);
		exit(2);
	}
}
