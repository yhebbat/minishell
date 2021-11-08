#include "../minishell.h"

int check_flag(char **args, int *x)
{
	int i;
	int j;
	int flag = 0;

	i = 1;

    *x = 1;
	while(args[i] && strncmp(args[i], "-n", 2) == 0)
	{
        flag = 1;
		j = 2;
		while(args[i][j])
		{
			if(args[i][j] != 'n')
            {
				flag = 0;
                return flag;
            }
			j++;
		}
		i++;
		*x = i;
	}
    return flag;
}


int	echo(char **args)
{
    int i;
    int flag;

    flag = check_flag(args, &i);

    while(args[i])
    {
        printf("%s", args[i]);
        if(args[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if(flag == 0)
        printf("\n");
    return(1);

}