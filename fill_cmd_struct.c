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
	// new_cmd = header->cmd_h;
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
	// ft_complet(header);
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
	int		r;
	char	*var;

	i = 0;
	k++;
	r = k;
	while (str[r] && str[r] != '"' && str[r] != ' ' && str[r] != '\'' && str[r] != '$')
	{
		i++;
		r++;
	}
	var = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[k] && str[k] != '"' && str[k] != ' ' && str[k] != '\'' && str[k] != '$')
		var[i++] = str[k++];
	var[i] = '\0';
	return (var);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*findit(t_headers *header, char *var)
{
	t_env	*checkenv;
	char	*str;

	checkenv = header->env_h;
	if (var[0] != '_' && !ft_isalpha(var[0]))
	{
		var++;
		str = ft_strdup(var);
		return(str);
	}
	while (checkenv)
	{
		if (!strcmp(checkenv->var, var))
		{
			str = ft_strdup(checkenv->val);
			return (str);
			break ;
		}
		checkenv = checkenv->suivant;
	}
	str = malloc(1);
	str[0] = '\0';
	return (str);
}
char *ft_strjoin_dollarfree(char *s1, char *s2)
{
	char *ret;

	ret = ft_strjoin_dollar(s1, s2);
	free (s1);
	return (ret);
}
char *ft_strjoin_free(char *s1, char *s2)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	free (s1);
	return (ret);
}
// void	checkdollar(t_headers *header)
// {
// 	t_cmds	*findollar;

// 	// t_env	*checkenv;
// 	int		i;
// 	int		k;
// 	int s_q;
// 	// int d_q;
// 	char	*var;
// 	char	*val;

// 	s_q = 0;
// 	i = 0;
// 	k = 0;
// 	findollar = header->cmd_h;
// 	// checkenv = header->envi;
// 	while (findollar)
// 	{
// 		i = 0;
// 		while (findollar->args[i])
// 		{
// 			k = 0;
// 			while (findollar->args[i][k])
// 			{
// 				if (findollar->args[i][k] == '\'')
// 					s_q++;
// 				if (findollar->args[i][k] == '$' && s_q % 2 == 0)
// 				{
// 					var = to_find(findollar->args[i], k);
// 					val = findit(header, var); // STILL HAVE A PRBLM WHEN U DON'T FIND THE VAR
// 					// printf("|%s|\n",var);
// 					// printf("|%s|\n",val);
// 					// printf("var---%s\nval---%s\n", var, val);
// 					findollar->args[i] = ft_strjoin_free(findollar->args[i], val);
// 					// add strjoin and modify on it
// 					free(var);
// 					free(val);
// 					// N.B.: YOU HAAVE TO FIND A WAY TO FREE VAR AND VAL
// 					break ;
// 				}
// 				k++;
// 			}
// 			i++;
// 		}
// 		findollar = findollar->next;
// 	}
// }

char	*ft_strstr(const char *src, const char *tofind)
{
	const char	*deb;
	const char	*fin;

	if (*tofind == '\0')
		return (char*)src;
	while (*src != '\0')
	{
		deb = src;
		fin = tofind;
		while (*src && *fin && *src == *fin)
		{
			src++;
			fin++;
		}
		if (*fin == '\0')
			return ((char *)src);
		src = deb + 1;
	}
	return (0);
}

void	checkdollar_cmd(t_headers *header)
{
	t_cmds	*new_cmd;
	int		i;
	int		s_q;
	int		d_q;
	char	*var;
	char	*val;
	char	*rest;

	new_cmd = header->cmd_h;
	s_q = 0;
	d_q = 0;
	i = 0;
	while (new_cmd)
	{
		i = 0;
		while (new_cmd->cmd[i])
		{
			if (new_cmd->cmd[i] == '\'' && (d_q % 2) == 0)
					s_q++;
			if (new_cmd->cmd[i] == '"' && (s_q % 2) == 0)
					d_q++;
			if (new_cmd->cmd[i] == '$' && s_q % 2 == 0)
			{
				var = to_find(new_cmd->cmd, i);
				printf("var---%s\n", var);
				rest = ft_strdup(ft_strstr(new_cmd->cmd, var));
				printf("rest---%s\n", rest);
				val = findit(header, var); // STILL HAVE A PRBLM WHEN U DON'T FIND THE VAR
				printf("val---%s\n", val);
				new_cmd->cmd = ft_strjoin_dollarfree(new_cmd->cmd, val);
				printf("cmd0---%s\n", new_cmd->cmd);
				new_cmd->cmd = ft_strjoin_free(new_cmd->cmd, rest);
				printf("cmd0---%s\n", new_cmd->cmd);
				free(var);
				free(val);
				free(rest);
			}
			i++;
		}
		new_cmd = new_cmd->next;
	}
}

void	save_cmd(t_headers *header, char **str)
{
	t_cmds	*new_cmd;
	
	before_save(header, str);
	checkdollar_cmd(header);
	ft_complet(header);
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