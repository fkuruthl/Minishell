/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_toklist_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:22:21 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:41:18 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_tok_quotes(char *str)
{
	int	i;
	int	state;
	int	quote;

	i = 0;
	state = STATE_GENERAL;
	while (str[i])
	{
		if ((str[i] == CHAR_SQUOTE || str[i] == CHAR_DQUOTE)
			&& (state == STATE_GENERAL))
		{
			quote = str[i];
			state = set_state(quote);
		}
		else if ((str[i] == CHAR_SQUOTE || str[i] == CHAR_DQUOTE)
			&& (state != STATE_GENERAL))
		{
			if (str[i] == quote)
				state = STATE_GENERAL;
		}
		i++;
	}
	if (state != STATE_GENERAL)
		return (quote);
	return (-1);
}

int	check_list_quotes(t_token *tok_list)
{
	int	quote;

	quote = -1;
	while (tok_list)
	{
		quote = check_tok_quotes(tok_list->data);
		if (quote != -1)
		{
			ft_dprintf(2, "Unexcpected EOF while looking for a matching '%c'\n",
				quote);
			return (0);
		}
		tok_list = tok_list->next;
	}
	return (1);
}
