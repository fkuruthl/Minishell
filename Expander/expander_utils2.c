/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:27:10 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	bool_stand_alone(char c, int state)
{
	if (is_wspace(c) || c == '\0' || (c == '"'
			&& state == IN_DQUOTE))
		return (printf("stand_alone\n"), 1);
	return (0);
}

int	not_stand_alone(char c1, char c2, int state)
{
	if (c1 == '$' && state != IN_SQUOTE
		&& !bool_stand_alone(c2, state))
		return (1);
	return (0);
}
