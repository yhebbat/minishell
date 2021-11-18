#include    "execution.h"

void	ft_env(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->env[i])
	{
		printf("%s\n", exec->env[i]);
		i++;	
	}
	__get_var(SETEXIT,0);
	//dprintf(1,"***** %d\n",__get_var(GETEXIT,0));
}
