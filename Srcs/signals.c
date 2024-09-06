/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:20:34 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/06 20:28:32 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	event(void)
{
	return (0);
}

void	child_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit\n");
	else if (sig == SIGINT)
		ft_dprintf(STDERR_FILENO, "\n");
}

void	init_child_signals(void)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler);
}

void	ft_sighandler(int sig)
{
	(void) sig;
	if (g_sigstat == IN_SHELL || g_sigstat == IN_CHILD)
	{
		g_sigstat = 130;
		ft_dprintf(2, "^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
	}
	else if (g_sigstat == IN_HDOC)
	{
		g_sigstat = OUT_HDOC;
		ft_dprintf(2, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	rl_event_hook = event;
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, SIG_IGN);
}
