#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h> 

int ft_pwd()
{
    char str[1024];
    
    if (getcwd(str, sizeof(str)) != NULL) 
    {
        printf("%s\n", str);
    } 
    else 
    {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

void my_print(const char *str)
{
    int i = 0;
    while (str[i]) 
    {
        write(1,&str[i++],1);
    }
    write(1,"\n",1);
}
void ft_echo(int ac, char **av)
{
    int i = 2;
    while(i < ac)
    {
        printf("%s", av[i]);
        i++;
        if(i < ac -1)
        {
            printf(" ");
        }
    }
}

int main(int ac, char **av, char **env)
{
    if (ac > 1 && (strcmp(av[1], "env") == 0)) 
    {
        while (*env) 
        {
            my_print(*env++);
        }
    }
    if (ac > 1 && (strcmp(av[1], "echo") == 0 || strcmp(av[1], "ECHO") == 0))
    {
        ft_echo(ac,av);
    }
    if (ac > 1 && (strcmp(av[1], "pwd") == 0 || strcmp(av[1], "PWD") == 0))
    {
        // ft_pwd();
        // char *av1[] = {"./a.out", "echo", "$PWD"};
        // ft_echo(3, av1);
        char *p = "$PWD";
        printf("%s", p);
    }
    if (ac > 1 && (strcmp(av[1], "cd") == 0 || strcmp(av[1], "CD") == 0))
    {
        
    }
    return 0;
}