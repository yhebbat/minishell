#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*suivant;
	struct s_env	*preced;
}t_env;

typedef struct s_headers
{
	struct s_env	*env_h;
	struct s_env	*env_f;
}t_headers;

char	**ft_split(char const *s, char c);
#endif