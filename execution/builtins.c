#include "../minishell.h"

/*
  Function Declarations for builtin shell commands:
 */
int	cd(char **args);
int	echo(char **args);
int pwd(char **args);
//int	env(char **args);
int	eexit(char **args);
//int	export(char **args);
//int	unset(char **args);


/*
  List of builtin commands, followed by their corresponding functions.
 */
char	*builtin_str[] =
{
	"cd",
	"echo",
	"pwd",
	//"env",
 	"exit"
	//"export",
	//"unset",
};

int (*builtin_func[]) (char **) =
{
	&cd,
	&echo,
	&pwd,
	//&env,
	&eexit
	//&export,
	//&unset,
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
		char*buf = getenv("HOME");
		if (buf == 0)
		{
			printf("HOME not set\n");
			return (1);
		}
		chdir(buf);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("grissen");
		}
	}
	return (1);
}

int	pwd(char **args)
{
	long n;
	char *buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", buf);
	}
	free(buf);
	return (EXIT_SUCCESS);
}

//int	export(char **args)
//{

//}

//int	unset(char **args)
//{

//}

//int	env(char **args)
//{

//}

int	eexit(char **args)
{
	return (0);
}
