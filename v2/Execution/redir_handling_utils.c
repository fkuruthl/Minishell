/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:16:45 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:26:25 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	memset_files_arr(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->f_amnt)
	{
		cmd->files[i].fname = NULL;
		cmd->files[i].type = 0;
		cmd->files[i].fd = 0;
		i++;
	}
}

void	init_delims_and_file_arr(t_ASTree *rdrnode, t_command *cmd)
{
	while (rdrnode)
	{
		if (rdrnode->type != NODE_HDOC)
			(cmd->f_amnt)++;
		else
			(cmd->hdoc_amnt)++;
		rdrnode = rdrnode->left;
	}
	if (cmd->f_amnt)
	{
		cmd->files = (t_fdata *)malloc(sizeof(t_fdata) * (cmd->f_amnt));
		memset_files_arr(cmd);
	}
	if (cmd->hdoc_amnt)
		cmd->delims = (char **)malloc(sizeof(char *) * (cmd->hdoc_amnt + 1));
}

int	assign_fds(t_ASTree *rdrnode, char *str)
{
	int	fd;
	DIR	*dir_res;

	fd = 0;
	dir_res = opendir(str);
	if (dir_res != NULL)
		return (closedir(dir_res), -2);
	if (rdrnode->type == NODE_RDIN)
		fd = open(str, O_RDONLY, 0777);
	if (rdrnode->type == NODE_RDOUT)
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (rdrnode->type == NODE_APND)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

void	error_close_fds(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->f_amnt && cmd->files[i].fname != NULL)
	{
		if (!(cmd->files[i].fd == -1 || cmd->files[i].fd == -2))
			close(cmd->files[i].fd);
		i++;
	}
}
