#include "../minishell.h"

int	execute(t_headers *header)
{
	t_cmds *ncmd;
	ncmd = header->cmd_h;
	int	i;
	if (!ncmd || !ncmd->args[0])
		return (1);
	i = 0;
	while(i < num_builtins())
	{
		if (strcmp(ncmd->args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(ncmd->args);
		i++;
	}
	return launch(header);
}