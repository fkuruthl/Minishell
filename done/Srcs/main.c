/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:12:22 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/01 01:41:24 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sigstat = IN_SHELL;

void	warn_message(void)
{
	ft_putstr_fd("Warning: Insufficient memory", 2);
	ft_putstr_fd(". Undefined behavior to be expected\n", 2);
}

void	init_shell(t_minishell *minishell)
{
	minishell->cmd_line = NULL;
	minishell->ast = NULL;
	minishell->tok_list = NULL;
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	minishell;

	(void) argc;
	(void) argv;
	minishell.binlist = assign_binlist();
	minishell.env = setup_envlist(env);
	minishell.exit_status = 0;
	while (1)
	{
		init_signals();
		init_shell(&minishell);
		minishell.cmd_line = readline("minishell: ");
		if (check_signal(&minishell) == e_continue)
			continue ;
		check_cmdline(&minishell);
		tokenizer(&minishell.tok_list, minishell.cmd_line);
		if (parse_quotes(&minishell) == e_continue)
			continue ;
		if (check_ast(&minishell) == e_continue)
			continue ;
		execute_job(&minishell, minishell.ast);
		main_cleanup(&minishell);
	}
	return (0);
}
