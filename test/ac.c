#include <stdio.h>
#include <unistd.h>
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
    } else 
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
        write(1, &str[i++], 1);
    }
    write(1, "\n", 1);
}


void ft_echo(int ac, char **av) 
{
    for (int i = 2; i < ac; i++) 
    {
        printf("%s", av[i]);
        if (i < ac - 1) 
        {
            printf(" ");
        }
    }
    printf("\n");
}


void ft_cd(int ac, char **av) 
{
    if (ac < 3) 
    {
        fprintf(stderr, "cd: expected argument to \"cd\"\n");
        return;
    }
    if (chdir(av[2]) != 0)
    {
        perror("cd");
    }
}

void ft_ls(const char *path) 
{
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) 
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) 
    {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}


void ft_cat(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("cat");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        printf("%s", buffer);
    }

    fclose(file);
}

int main(int ac, char **av, char **env) 
{
    if (ac > 1 && strcmp(av[1], "env") == 0) 
    {
        while (*env) 
        {
            my_print(*env++);
        }
    } 
    else if (ac > 1 && (strcmp(av[1], "echo") == 0 || strcmp(av[1], "ECHO") == 0)) 
    {
        ft_echo(ac, av);
    } 
    else if (ac > 1 && (strcmp(av[1], "pwd") == 0 || strcmp(av[1], "PWD") == 0)) 

    {
        ft_pwd();
    } 
    else if (ac > 1 && (strcmp(av[1], "cd") == 0 || strcmp(av[1], "CD") == 0))
    {
        ft_cd(ac, av);
    } 
    else if (ac > 1 && (strcmp(av[1], "ls") == 0 || strcmp(av[1], "LS") == 0)) 
    {
        if (ac < 3) {
            ft_ls(".");
        } else {
            ft_ls(av[2]);
        }
    } else if (ac > 1 && (strcmp(av[1], "cat") == 0 || strcmp(av[1], "CAT") == 0))
    {
        if (ac < 3) {
            fprintf(stderr, "cat: expected argument to \"cat\"\n");
        } else {
            ft_cat(av[2]);
        }
    } else {
        fprintf(stderr, "Unsupported command: %s\n", av[1]);
    }
    return 0;
}

