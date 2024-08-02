/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:11:03 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:38:14 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_cleanup(t_minishell *shell)
{
	free(shell->cmd_line);
	delete_list(shell->tok_list);
	delete_node(shell->ast);
}

int	check_signal(t_minishell *shell)
{
	if (g_sigstat == 130)
	{
		free(shell->cmd_line);
		shell->exit_status = g_sigstat;
		g_sigstat = IN_SHELL;
		return (e_continue);
	}
	return (e_normal);
}

void	check_cmdline(t_minishell *shell)
{
	if (!(shell->cmd_line))
	{
		main_cleanup(shell);
		delete_env_list(shell);
		delete_binlist(shell->binlist);
		printf("exit\n");
		exit(0);
	}
	else
		add_history(shell->cmd_line);
}

int	parse_quotes(t_minishell *shell)
{
	if (!check_list_quotes(shell->tok_list))
	{
		main_cleanup(shell);
		shell->exit_status = 2;
		return (e_continue);
	}
	return (e_normal);
}

int	check_ast(t_minishell *shell)
{
	if (generate_ast(shell) == 0)
	{
		main_cleanup(shell);
		return (e_continue);
	}
	return (e_normal);
}
