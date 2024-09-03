/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:21:10 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:24:09 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef enum s_mode
{
	NO_MODE,
	MODE_RDIN,
	MODE_RDOUT,
	MODE_HDOC,
	MODE_APND
}	t_mode;

typedef struct s_fdata
{
	char	*fname;
	int		type;
	int		fd;
}	t_fdata;

typedef struct s_command {
	int		*pids;
	int		pid_i;
	char	**delims;
	t_fdata	*files;
	int		f_amnt;
	int		hdoc_amnt;
	char	*rdin_f;
	char	*rdout_f;
	char	*append_f;
	int		fd_in;
	int		fd_hdoc;
	int		fd_out;
	int		fd_apnd;
	char	*cmd_path;
	char	*cmd_full_path;
	char	**cmd_args;
	int		in_mode;
	int		out_mode;
	int		stdin_pipe;
	int		stdout_pipe;
	int		piperead;
	int		pipewrite;
	int		copy_rd_fd;
	int		save_stdin;
	int		save_stdout;
}	t_command;

//redir.c
void	print_fdata(t_command *cmd);
void	print_delims_arr(char **arr);

#endif