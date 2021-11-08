#include "../minishell.h"

int	execute(t_headers *header)
{
	t_cmds *ncmd;
	ncmd = header->cmd_h;
	int	i;

	if (!ncmd || ncmd->args[0] == NULL)
	{
		return (1);
	}
	i = 0;
	while(i < 3)
	{
		if (strcmp(ncmd->args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(ncmd->args);
		i++;
	}
	return launch(header);
}