#include    "execution.h"

void    unset(t_cmds *cmd, t_exec *exec, t_headers *header)
{
    int t;
    t_env *exist_env;
    t_env *env;
    char *str;

    env = header->env_h;
    t = 1;
    env = header->env_h;
    while (cmd->args[t])
    {
        //eq==0 no =
        //eq==1 =
        //eq==2 +=
        //eq==-1 error not a valid identifier
        // k = 0;
        if (cmd->args[t][0] != '_' && ft_isalpha(cmd->args[t][0]) == 0)
        {
            printf("export: `%s': not a valid identifier\n", cmd->args[t]);
            // break ;
        }
        else
        {
            str = ft_strdup(cmd->args[t]);
            // printf("%s||%s||*%d*\n", str[0], str[1],eq);
            exist_env = find_var_env(str, env);
            if (exist_env)
            {
                // while (env && ft_strcmp(env->var, str) == 0)
                // {
                if (exist_env->preced == NULL && exist_env->suivant)
                {
                    header->env_h = exist_env->suivant;
                    free(exist_env);
                }
                else if (exist_env->preced && exist_env->suivant)
                {
                    exist_env->preced->suivant = exist_env->suivant;
                    free(exist_env);
                }
                else if (exist_env->preced && exist_env->suivant == NULL)
                {
                    exist_env->preced->suivant = NULL;
                    free(exist_env);
                }
                //     env = env->suivant;
                // }
    		}
            free(str);  
        }
        t++;
    }
    fill_env2(exec, header);
}
