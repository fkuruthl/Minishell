/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:55 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/03 12:35:16 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_wspace(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

void	add_to_list(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!lst)
		return ;
	new->next = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}

void	add_node_data(t_token *tok_node, t_tokenType type)
{
	if (type == CHAR_PIPE)
		tok_node->data = ft_strdup("|");
	else if (type == CHAR_HDOC)
		tok_node->data = ft_strdup("<<");
	else if (type == CHAR_APND)
		tok_node->data = ft_strdup(">>");
	else if (type == CHAR_RDIN)
		tok_node->data = ft_strdup("<");
	else if (type == CHAR_RDOUT)
		tok_node->data = ft_strdup(">");
	if (tok_node->data == NULL)
		warn_message();
}

void	delete_list(t_token *token_list)
{
	if (token_list)
		delete_list(token_list->next);
	else
		return ;
	if (token_list->data)
		free(token_list->data);
	free(token_list);
}
