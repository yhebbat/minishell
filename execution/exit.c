#include "execution.h"
#include <ctype.h>

void	half_ft_exit(char **args)
{
	int	j;

	j = 0;
	while (args[1][j])
	{
		if (!(isdigit(args[1][j])))
		{
			write(2, "exit\n", 6);
			write(2, "minishell: exit:", 17);
			write(2, args[1], ft_strlen(args[1]));
			write(2, "numeric argument required", 26);
			exit(255);
		}
		j++;
	}
	if (args[2] == NULL)
	{
		__get_var(SETEXIT, atoi(args[1]));
		write(2, "exit\n", 6);
		exit(__get_var(GETEXIT, 0));
	}
}

int	ft_exit(t_headers *headers)
{
	char	**args;

	args = headers->cmd_h->args;
	if (!args[1])
	{
		write(2, "exit\n", 6);
		exit(__get_var(GETEXIT, 0));
	}
	if (args[2] != NULL)
	{
		write(2, "exit\n", 6);
		write(2, "minishell: exit: too many arguments\n", 37);
		__get_var(SETEXIT, 1);
		return (1);
	}
	half_ft_exit(args);
	return (0);
}
