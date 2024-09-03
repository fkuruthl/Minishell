/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:20:34 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/03 12:35:53 by hsalah           ###   ########.fr       */
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

// rl_replace_line("", 0); does not do anything!
void	ft_sighandler(int sig)
{
	(void) sig;
	if (g_sigstat == IN_SHELL || g_sigstat == IN_CHILD)
	{
		g_sigstat = 130;
		ft_dprintf(2, "^C\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_done = 1; >>> Hamsa: add comment
	}
	else if (g_sigstat == IN_HDOC)
	{
		g_sigstat = OUT_HDOC;
		ft_dprintf(2, "\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_done = 1; >>> Hamsa: add comment
	}
}

// Without rl_catch_sigals = 0, then when we hit ctrl + C
// in the shell prompt, it would display ^C and if we hit
// ctrl + \ it would display ^\. So to avoid that, we use
// the rl_catch_sigals = 0, which is basically like
// SIG_IGN for the readline library. 
void	init_signals(void)
{
	// rl_catch_signals = 0; >>> Hamsa: add comment
	// rl_event_hook = event; >>> Hamsa: add comment
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, SIG_IGN);
}
