#include<unistd.h>
#include<stdio.h>
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

// void ft_pwd(char *str)
// {
//     (void)str;
//     char *av[3] = {"das", "Dsa", "$PWD"};
//     ft_echo(3, av);
// }

// int main(int ac, char **av)
// {
//     if (av[3][0] == 'p')
//         ft_pwd(" ");
//     // ft_echo(ac, av);
// }

