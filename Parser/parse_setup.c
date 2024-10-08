/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:11:59 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/06 20:29:10 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	base_case(t_tokenType tok_type, t_token **tok_node, char **data)
{
	int	i;

	i = 0;
	if (*tok_node == NULL)
		return (0);
	if ((*tok_node)->type != tok_type)
		return (0);
	if (data)
	{
		if (!(*tok_node)->data)
			return (0);
		while ((*tok_node)->data[i])
			i++;
		*data = (char *)malloc(1 * (i + 1));
		if (!(*data))
			return (warn_message(), 0);
		ft_strlcpy(*data, (*tok_node)->data, i + 1);
	}
	(*tok_node) = (*tok_node)->next;
	return (1);
}

static void	ast_parse_messages(t_minishell *shell, t_token *head)
{
	t_token	*next;

	next = (shell->tok_list)->next;
	if (head->type == CHAR_PIPE)
	{
		ft_dprintf(2, "syntax error near unexpected token '|'\n");
		shell->exit_status = 2;
		return ;
	}
	if (next)
		ft_dprintf(2, "syntax error near unexpected token '%s'\n", next->data);
	else
		ft_dprintf(2, "syntax error near unexpected token 'newline'\n");
	shell->exit_status = 2;
}

int	generate_ast(t_minishell *shell)
{
	t_token	*save;

	save = shell->tok_list;
	shell->ast = cmdline(&(shell->tok_list));
	if ((shell->tok_list) != NULL)
	{
		ast_parse_messages(shell, save);
		return (shell->tok_list = save, 0);
	}
	return (shell->tok_list = save, 1);
}
