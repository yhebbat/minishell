#include    "execution.h"

char    *check_eq(char *str, int *eq)
{
    int i;
    int k;
    char *ret;

    i = 0;
    k = 0;
    while (str[i])
    {
        if (str[i] == '+' && str[i + 1] != '=')
        {
            *eq = -1;
            printf("export: `%s': not a valid identifier\n", str);
            break;
        }
        else if (str[i] == '+' && str[i + 1] == '=')
        {
            *eq = 2;
            break;
        }
        else if (str[i] == '=')
        {
            *eq = 1;
            break;
        }
        i++;
        *eq = 0;
    }
    if (*eq == 0 || *eq == -1)
        ret = ft_strdup(str);
    else if (*eq == 2 || *eq == 1)
    {
        ret = malloc(sizeof(char) * (i + 1));
        if (!ret)
            return (0);
        while (str[k] && k < i)
        {
            ret[k] = str[k];
            k++;
        }
        ret[k] = '\0';
    }
    return (ret);
}

char    *fill_exportval(char *str, int *eq)
{
    int i;
    int k;
    char *ret;

    i = 0;
    k = 0;
    while (str[i])
    {
        if (str[i] == '+' && str[i + 1] != '=')
            break;
        else if (str[i] == '+' && str[i + 1] == '=')
            break;
        else if (str[i] == '=')
            break;
        i++;
    }
    if (*eq == 0 || *eq == -1)
        ret = NULL;
    else if (*eq == 1 ||*eq == 2 )
        ret = ft_strdup(&str[i + *eq]);
    // else if (*eq == 2)
    //     ret = ft_strdup(str + i + 2);
    return (ret);
}

t_env   *find_var_env(char  str, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(str, env->var) == 0)
            return (env);
        env = env->suivant;
    }
    return (NULL);
}

void    export(t_cmds *cmd, t_exec *exec, t_headers *header)
{
    int t;
    int k;
    int eq;
    t_env *exist_env;
    t_env *env;
    char **str;

    env = header->env_h;
    k = 0;
    t = 1;
    if (!cmd->args[t])
    {
        //print "declare -x env"
    }
    while (cmd->args[t])
    {
        str = malloc(sizeof(char *) * 3);
        eq = 0;
        //eq==0 no =
        //eq==1 =
        //eq==2 +=
        //eq==-1 error not a valid identifier
        k = 0;
        if (cmd->args[t][0] != '_' && ft_isalpha(cmd->args[t][0]) == 0)
        {
            printf("export: `%s': not a valid identifier", cmd->args[t]);
            break ;
        }
        str[0] = check_eq(cmd->args[t], &eq);
        str[1] = fill_exportval(cmd->args[t], &eq);
        str[2] = 0;
        printf("%s||%s||*%d*\n", str[0], str[1],eq);
        exist_env = find_var_env(str[0], env);
        if (eq == 0 && exist_env)
        {
            //dont modify it
        }
        if (eq == 0 && !exist_env)
        {
			ft_addbottom(header, str[0], NULL);
			//add it with val = NULL
		}
        if (eq == 1 && exist_env)
        {
			exist_env->val = ft_strjoin_free(exist_env->val, str[1]);
			//modify it
		}
        if (eq == 1  && !exist_env)
        {
			ft_addbottom(header, str[0], str[1]);
			//add it with val = 
		}
        if (eq == 2  && exist_env)
        {
			exist_env->val = ft_strjoin_free(exist_env->val, str[1]);
			//add it with val += 
		}
        if (eq == 2  && !exist_env)
        {
			ft_addbottom(header, str[0], str[1]);
			//add it with val = 
		}
        ft_free(str);
        t++;
    }
    
}
