#include "minishell.h"

void	ft_addbotcmd(t_headers *head, char *val)
{
	t_cmds	*stack;
	t_cmds	*to_add;

	to_add = malloc(sizeof(t_cmds));
	if (!to_add)
		exit(0);
	if (head->cmd_h == NULL)
	{
		to_add->cmd = add_str(val);
		// to_add->val = add_str(val);
		to_add->next = NULL;
		to_add->prec = NULL;
		head->cmd_f = to_add;
		head->cmd_h = to_add;
	}
	else
	{
		stack = head->cmd_f;
		// to_add->var = add_str(var);
		to_add->cmd = add_str(val);
		to_add->prec = stack;
		to_add->next = NULL;
		stack->next = to_add;
		head->cmd_f = to_add;
	}
}

void	ft_delbotcmd(t_headers *head)
{
	t_cmds	*to_delete;
	t_cmds	*stack;

	if (head != NULL && head->cmd_h != NULL)
	{
		to_delete = head->cmd_f;
		if (!to_delete->prec)
		{
			ft_free(to_delete->args);
			free(to_delete->cmd);
			// free(to_delete->var);
			free(to_delete);
			head->cmd_h = NULL;
			head->cmd_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->prec;
			head->cmd_f = stack;
			stack->next = NULL;
			ft_free(to_delete->args);
			// free(to_delete->val);
			free(to_delete->cmd);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

void	ft_complet(t_headers *header)
{
	t_cmds *new_cmd;
	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		new_cmd->args = ft_flex(new_cmd->cmd, ' ');
		new_cmd = new_cmd->next;
	}
	// new_cmd = header->cmd_h;
	// while (new_cmd)
	// {
	// 	int i = 0;
	// 	int k = 0;
	// 	while (new_cmd->args[i])
	// 	{
	// 		k = 0;
	// 		if (new_cmd->args[i][k] != '\'')
	// 		{
	// 			while (new_cmd->args[i][k])
	// 			{
	// 				if (new_cmd->args[i][k] == '$')
	// 				{

	// 				}
	// 				k++;
	// 			}
	// 		}
	// 		i++;
	// 	}
	// 	new_cmd = new_cmd->next;
	// }
	new_cmd = header->cmd_h;
	// while (new_cmd)
	// {
	// 	int i = 0;
	// 	while (new_cmd->args[i])
	// 	{
	// 		printf("%s\n",new_cmd->args[i]);
	// 		i++;
	// 	}
	// 	printf("----------------------\n");
	// 	new_cmd = new_cmd->next;
	// }
	new_cmd = header->cmd_h;
	//to free this sturct u have to call ft_freeee inside ft_delstruct 
}

void	before_save(t_headers *header, char	**str)
{
	int i;

	i = 0;
	while (str[i])
	{
		// printf("|%s|\n",str[i]);
		ft_addbotcmd(header, str[i]);
		i++;
	}
	ft_complet(header);
	// t_cmds *new_cmd;
	// new_cmd = header->cmd_h;
	// while (new_cmd)
	// {
		
	// 	printf("%s\n", new_cmd->cmd);
	// 	new_cmd = new_cmd->next;
	// }
}

char	*to_find(char *str, int k)
{
	int		i;
	char	*var;

	i = strlen(str);
	var = malloc(sizeof(char) * (i - k + 1));
	i = 0;
	k++;
	while (str[k])
		var[i++] = str[k++];
	var[i] = '\0';
	return (var);
}

char	*findit(t_headers *header, char *var)
{
	t_env	*checkenv;
	char	*str;

	checkenv = header->env_h;
	while (checkenv)
	{
		if (!strcmp(checkenv->var, var))
		{
			str = checkenv->val;
			break ;
		}
		checkenv = checkenv->suivant;
	}
	if (strcmp(checkenv->var, var) != 0)
	{
		str = malloc(1);
		str = "\n";
	}
	return (str);
}

void	checkdollar(t_headers *header)
{
	t_cmds	*findollar; //RIB7 MINA L INTERNET

	// t_env	*checkenv;
	char	*var;  // PENALTY
	char	*val; //  KOFLA
	int		i;
	int		k;

	i = 0;
	k = 0;
	findollar = header->cmd_h;
	// checkenv = header->envi;
	while (findollar)
	{
		i = 0;
		while (findollar->args[i])
		{
			k = 0;
			while (findollar->args[i][k])
			{
				if (findollar->args[i][k] == '$')
				{
					var = to_find(findollar->args[i], k);
					val = findit(header, var); // STILL HAVE A PRBLM WHEN U DON'T FIND THE VAR
					printf("var---%s\nval---%s\n", var, val);
					findollar->args[i] = ft_strjoin(findollar->args[i], val);
					// add strjoin and modify on it
					// free(var);
					// free(val);
					// N.B.: YOU HAAVE TO FIND A WAY TO FREE VAR AND VAL
					break ;
				}
				k++;
			}
			i++;
		}
		findollar = findollar->next;
	}
	// free(var);
	// free(val);
}

void	save_cmd(t_headers *header, char **str)
{
	t_cmds	*new_cmd;
	before_save(header, str);
	checkdollar(header);
	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		int i = 0;
		while (new_cmd->args[i])
		{
			printf("%s\n",new_cmd->args[i]);
			i++;
		}
		printf("----------------------\n");
		new_cmd = new_cmd->next;
	}
	// save(header, str);
	while (header->cmd_h)
		ft_delbotcmd(header);
}