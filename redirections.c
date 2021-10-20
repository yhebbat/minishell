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

void	checkredirection_cmd(t_headers *header)
{
    t_cmds	*find_redirection;
	int i;
	int	red;

	i = 0;
	find_redirection = header->cmd_h;
	while (find_redirection)
	{
		while (find_redirection->cmd[i])
		{
			if (find_redirection->cmd[i] == '>' || find_redirection->cmd[i] == '<')
			{
				red = redcounter(find_redirection->cmd, i);
			}
			i++;
		}
		find_redirection = find_redirection->next;
	}
}