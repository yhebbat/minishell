#include "minishell.h"

void	ft_addbotfile(t_cmds *head, char *val, int type)
{
	t_file	*stack;
	t_file	*to_add;

	to_add = malloc(sizeof(t_file));
	if (!to_add)
		exit(0);
	if (head->file_h == NULL)
	{
		to_add->filename = add_str(val);
		to_add->type = type;
		to_add->next = NULL;
		to_add->prec = NULL;
		head->file_f = to_add;
		head->file_h = to_add;
	}
	else
	{
		stack = head->file_f;
		to_add->filename = add_str(val);
		to_add->type = type;
		to_add->prec = stack;
		to_add->next = NULL;
		stack->next = to_add;
		head->file_f = to_add;
	}
}

void	ft_delbotfile(t_cmds *head)
{
	t_file	*to_delete;
	t_file	*stack;

	if (head != NULL && head->file_h != NULL)
	{
		to_delete = head->file_f;
		if (!to_delete->prec)
		{
			free(to_delete->filename);
			free(to_delete);
			head->file_h = NULL;
			head->file_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->prec;
			head->file_f = stack;
			stack->next = NULL;
			free(to_delete->filename);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

int		redcounter(char *str, int i)
{
	int		d;

	d = 0;
	while (str[i] && str[i] == '$')
	{
		i++;
		d++;
	}
	return (d);	
}

char	*find_red(char *str, int k, int *red)
{
	int		i;
	int		r;
	char	*var;

	i = 0;
	r = k;
	if (str[r] == '>' && str[r + 1] != '>')
		*red = ONE;
	else if (str[r] == '>' && str[r + 1] == '>')
		*red = TWO;
	else if (str[r] == '<' && str[r + 1] != '<')
		*red = ONEREV;
	else if (str[r] == '<' && str[r + 1] == '<')
		*red = TWOREV;
	while (str[r] == '>' || str[r] == '<' || str[r] == ' ')
	{
		i++;
		r++;
	}
	while (str[r] && str[r] != ' ' && str[r] != '>' && str[r] != '<')
	{
		i++;
		r++;
	}
	var = malloc(sizeof(char) * (i + 1));
	r = i;
	i = 0;
	while (i < r/*str[k] && str[k] != '"' && str[k] != ' ' && str[k] != '\'' && str[k] != '$'*/)
		var[i++] = str[k++];
	var[i] = '\0';
	return (var);
}

char	*findredtosave(char *var)
{
	int		i;
	int		k;
	int		t;
	char	*ret;

	k = 0;
	t = 0;
	i = 0;
	while (var[i] == '>' || var[i] == '<' || var[i] == ' ')
		var++;
	t = i;
	while (var[i] && var[i] != '>' && var[i] != '<' && var[i] != ' ')
	{
		i++;
		k++;
	}
	ret = malloc(sizeof(char) * (k + 1));
	k = 0;
	while (k < i)
	{
		ret[k] = var[k];
		k++;
	}
	ret[k] = '\0';
	return (ret);
}

char *ft_strjoin_redfree(char *s1, char *s2, int i)
{
	char *ret;

	ret = ft_strjoin_red(s1, s2, i);
	free (s1);
	return (ret);
}

void	checkredirection_cmd(t_headers *header)
{
    t_cmds	*find_redirection;
	int i;
	int	red;
	int	s_q;
	int	d_q;
	char	*var;
	char	*val;
	char	*rest;

	i = 0;
	red = 0;
	find_redirection = header->cmd_h;
	while (find_redirection)
	{
		i = 0;
		red = 0;
		s_q = 0;
		d_q = 0;
		while (find_redirection->cmd[i])
		{
			// printf("[%c]\n",find_redirection->cmd[i]);
			if (find_redirection->cmd[i] == '\''/* && (d_q % 2) == 0*/)
					s_q++;
			if (find_redirection->cmd[i] == '"'/* && (s_q % 2) == 0*/)
					d_q++;
			if ((find_redirection->cmd[i] == '>' || find_redirection->cmd[i] == '<') && !(d_q % 2) && !(s_q % 2))
			{
				var = find_red(find_redirection->cmd, i, &red);
				// printf("var ---%s\n", var);
				// printf("type ---%d\n", red);
				rest = ft_strdup(ft_strstr(find_redirection->cmd + i, var));
				// printf("rest---%s\n", rest);
				val = findredtosave(var);
				find_redirection->cmd = ft_strjoin_redfree(find_redirection->cmd, rest, i);
				ft_addbotfile(find_redirection, val, red);
				i = -1;
				free(var);
				free(val);
				free(rest);
			}
			i++;
		}
		find_redirection = find_redirection->next;
	}
}