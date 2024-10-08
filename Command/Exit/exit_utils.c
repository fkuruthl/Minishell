/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:07:12 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:16:15 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_exit_args(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd->cmd_args)
		return (0);
	while (cmd->cmd_args[i])
		i++;
	return (i - 1);
}

int	bool_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	full_free(t_minishell *shell, t_command *cmd)
{
	free(shell->cmd_line);
	delete_command(cmd);
	delete_list(shell->tok_list);
	delete_node(shell->ast);
	delete_binlist(shell->binlist);
	delete_env_list(shell);
}
