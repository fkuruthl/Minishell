#include <unistd.h> 
// int main(int ac, char **av)
// {
//     char str[];
//     if(strcmp(av[1], "PWD"))
//     {
//        str = getcwd;
//     }
//     printf("%s",str);
// }

#include <stdio.h>
#include <unistd.h> 
#include <string.h> 


int main(int ac, char **av) 
{
    char str[1024];
    if (ac > 1 && (strcmp(av[1], "pwd") == 0 || strcmp(av[1], "PWD") == 0))
    {
        if (getcwd(str, sizeof(str)) != NULL) 
        {
            printf("%s\n", str);
        } 
        else 
        {
            perror("getcwd() error");
            return 1;
        }
    }
    return 0;
}

