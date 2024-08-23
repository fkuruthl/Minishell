#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <errno.h>
#include <dirent.h>

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
void ft_cd(int ac, char **av)
{
    // if (ac < 3)
    // {
    //     fprintf(stderr, "cd: expected argument to \"cd\"\n");
    //     return;
    // }
    if (chdir(av[2]) != 0)
    {
        perror("cd");
    }
}
void ft_ls(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
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
        ft_pwd();
    }
    if (ac > 1 && (strcmp(av[1], "cd") == 0 || strcmp(av[1], "CD") == 0))
    {
        ft_cd(ac,av);
    }
    if (ac > 1 && (strcmp(av[1], "ls") == 0 || strcmp(av[1], "LS") == 0))
    {
        ft_ls(av[2]);
    }
    if (ac > 1 && (strcmp(av[1], "cat") == 0 || strcmp(av[1], "CAT") == 0))
    {
        ft_ls(av[2]);
    }
    if
    return 0;
}

