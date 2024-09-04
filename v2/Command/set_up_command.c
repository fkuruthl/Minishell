/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:33:31 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:37:21 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_empty_expand(t_minishell *shell, char *str)
{
	char	*expansion;

	if (str[0] != '$')
		return (0);
	expansion = expand_str(str, shell->env, shell->exit_status);
	if (!expansion[0])
		return (free(expansion), 1);
	return (free(expansion), 0);
}

static void	copy_cmd_args(t_ASTree *node, t_minishell *shell, t_command *cmd)
{
	char	*expansion;
	char	**split_expansion;
	int		i;
	int		j;

	j = 0;
	while (node)
	{
		i = 0;
		if (!check_empty_expand(shell, node->data))
		{
			expansion = q_expand_str(node->data, shell->env,
					shell->exit_status);
			split_expansion = split_with_quotes(expansion);
			while (split_expansion[i])
				cmd->cmd_args[j++] = strip_quotes(split_expansion[i++]);
			free(expansion);
			delete_2d_arr(split_expansion);
		}
		node = node->left;
	}
	cmd->cmd_args[j] = NULL;
}

int	count_cmd_args(t_ASTree *node, t_minishell *shell)
{
	char	*expansion;
	char	**split_expansion;
	int		arg_count;
	int		i;

	arg_count = 0;
	while (node)
	{
		i = 0;
		if (!check_empty_expand(shell, node->data))
		{
			expansion = q_expand_str(node->data, shell->env,
					shell->exit_status);
			split_expansion = split_with_quotes(expansion);
			while (split_expansion[i])
			{
				arg_count++;
				i++;
			}
			delete_2d_arr(split_expansion);
			free(expansion);
		}
		node = node->left;
	}
	return (arg_count);
}

void	set_up_cmd_members(t_ASTree *node, t_minishell *shell, t_command *cmd)
{
	copy_cmd_args(node, shell, cmd);
	if (cmd->cmd_args[0])
		cmd->cmd_path = ft_strdup(cmd->cmd_args[0]);
	else
		cmd->cmd_path = NULL;
}
