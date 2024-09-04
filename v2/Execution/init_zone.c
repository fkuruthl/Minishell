/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:23:01 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:26:03 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*set_pid_arr(int proc_count)
{
	int	*buffer;

	buffer = (int *)malloc(sizeof(int) * proc_count);
	return (buffer);
}

int	init_command(t_command *command, int proc_count)
{
	if (!command)
		return (warn_message(), 0);
	command->pids = set_pid_arr(proc_count);
	command->pid_i = 0;
	command->delims = NULL;
	command->rdin_f = NULL;
	command->rdout_f = NULL;
	command->append_f = NULL;
	command->files = NULL;
	command->f_amnt = 0;
	command->hdoc_amnt = 0;
	command->fd_in = 0;
	command->fd_hdoc = 0;
	command->fd_out = 0;
	command->fd_apnd = 0;
	command->cmd_path = NULL;
	command->cmd_full_path = NULL;
	command->cmd_args = NULL;
	command->in_mode = NO_MODE;
	command->out_mode = NO_MODE;
	command->save_stdin = 0;
	command->save_stdout = 0;
	return (1);
}

void	init_pipe_command(t_command *command)
{
	command->delims = NULL;
	command->rdin_f = NULL;
	command->rdout_f = NULL;
	command->append_f = NULL;
	command->files = NULL;
	command->f_amnt = 0;
	command->hdoc_amnt = 0;
	command->fd_in = 0;
	command->fd_hdoc = 0;
	command->fd_out = 0;
	command->fd_apnd = 0;
	command->cmd_path = NULL;
	command->cmd_full_path = NULL;
	command->cmd_args = NULL;
	command->in_mode = NO_MODE;
	command->out_mode = NO_MODE;
}
