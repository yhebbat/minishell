#include "../minishell.h"

/*
  Function Declarations for builtin shell commands:
 */
int	cd(char **args);
//int	exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char	*builtin_str[] =
{
	"cd",
	"exit"
};

int (*builtin_func[]) (char **) =
{
	&cd,
	&exit
};


int	num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int	cd(char **args)
{
	if (!args[1])
	{
		printf("expected argument");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			printf("error");
		}
	}
	return (1);
}

//int	exit(char **args)
//{
//	return (0);
//}