/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-cmdline_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:28:36 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:33:45 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ASTree	*cmdline(t_token **token_list)
{
	t_token		*save;
	t_ASTree	*node;

	save = *token_list;
	node = cmdline5(token_list);
	if (node)
		return (node);
	*token_list = save;
	return (NULL);
}

t_ASTree	*cmdline5(t_token **token_list)
{
	return (job(token_list));
}
