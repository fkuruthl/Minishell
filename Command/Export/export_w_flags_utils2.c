/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_w_flags_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:12:11 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:36:18 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	bool_syntax_validity(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (c == '_')
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (0);
}

int	check_export_syntax(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
	{
		ft_dprintf(2, "-minishell: export: '%s': not a valid identifier\n",
			str);
		return (0);
	}
	i++;
	while (str[i] != '=' && str[i])
	{
		if (!bool_syntax_validity(str[i]))
		{
			ft_dprintf(2, "-minishell: export: '%s': not a valid identifier\n",
				str);
			return (0);
		}
		i++;
	}
	return (1);
}
