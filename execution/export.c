#include    "execution.h"
/*
char    *check_eq(char *str, int *eq)
{
    int i;
    char    

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {

        }
        i++;
    }
    return (0);
}
*/
void    export(t_cmds *cmd, t_exec *exec)
{
    int t;
    int k;
    int eq;
    char **str;

    k = 0;
    t = 1;
    str = malloc(sizeof(char *) * 3);
    if (!cmd->args[t])
    {
        //print "declare -x env"
    }
    while (cmd->args[t])
    {
        eq = 0;
        k = 0;
        if (cmd->args[t][k] != '_' && is_alpha(cmd->args[t][k]) == 0)
        {
            printf("export: `%s': not a valid identifier", cmd->args[t]);
        }
        while (cmd->args[t][k])
        {
            str[0] = check_eq(cmd->args[t], &eq);
            // str[0] = ft_fill();
            k++;
        }
        ft_free(str);
        t++;
    }
    
}