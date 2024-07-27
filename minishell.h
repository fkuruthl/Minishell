#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

typedef struct s_shell {
    char **env;
    char *prompt;
    // Add other necessary fields
} t_shell;

void init_shell(t_shell *shell, char **envp);
void run_shell(t_shell *shell);
void cleanup_shell(t_shell *shell);

#endif
