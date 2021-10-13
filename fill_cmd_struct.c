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
	//to free this sturct u have to call ft_freeee inside ft_delstruct 
}

void	before_save(t_headers *header, char	**str)
{
	int i;

	i = 0;
	while (str[i])
	{
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

void	save_cmd(t_headers *header, char **str)
{
	before_save(header, str);
	// save(header, str);
	while (header->cmd_h)
		ft_delbotcmd(header);
}