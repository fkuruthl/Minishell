/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:00:59 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:31:10 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*q_expand_str(char *str, char *env[], int exit_status)
{
	char	*q_expanded;

	q_expanded = expansion(str, env, exit_status);
	return (q_expanded);
}

char	*expand_str(char *str, char *env[], int exit_status)
{
	char	*stripped;

	str = expansion(str, env, exit_status);
	stripped = strip_quotes(str);
	free(str);
	return (stripped);
}
