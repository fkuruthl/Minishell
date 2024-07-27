#include "minishell.h"

int main(int argc, char **argv, char **envp) 
{
    (void)argc;
    (void)argv;
    t_shell shell;

    init_shell(&shell, envp);
    run_shell(&shell);
    cleanup_shell(&shell);

    return 0;
}
