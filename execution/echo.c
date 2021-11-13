#include    "execution.h"

int    ft_check_newline(t_cmds *cmd, int *t)
{
    int k;
    // int t;

    k = 0;
    // t = 1;
    while (cmd->args[*t])
    {
        k = 0;
        if (cmd->args[*t][k] == '-')
        {
            k++;
            while (cmd->args[*t][k] == 'n')
                k++;
            if (cmd->args[*t][k])
                return (0);
        }
        (*t)++;
    }
    return (1);
}

void    echo(t_cmds *cmd)
{
    int i;
    int t;

    i = 0;
    t = 1;
    if (cmd->args[1])
    {
       i = ft_check_newline(cmd, &t);
       if (t != 1 && i == 0)
       {
           //print from args[t] without new line
           while (cmd->args[t])
           {
               write(2, cmd->args[t -1], ft_strlen(cmd->args[t -1]));
               t++;
           }
           write(2, "\n", 1);
       }
       else if (t == 1)
       {
         //print from args[t -1] with new line
           while (cmd->args[t - 1])
           {
                write(2, cmd->args[t -1], ft_strlen(cmd->args[t -1]));
            //    printf("%s",cmd->args[t]);
               t++;
           }
       }
    }
    else
        write(1, "\n", 1);

    //todo
}