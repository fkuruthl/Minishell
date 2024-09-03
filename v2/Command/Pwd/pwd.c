/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:49:34 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:17:59 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_minishell *shell)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir) 
		return (shell->exit_status = 1, 1);
	ft_dprintf(1, "%s\n", current_dir);
	free(current_dir);
	return (shell->exit_status = 0, 0);
}
