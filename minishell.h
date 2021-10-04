#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*suivant;
	struct s_env	*preced;
}t_env;

typedef struct s_henv
{
	struct s_env	*header;
	struct s_env	*footer;
}t_henv;

char	**ft_split(char const *s, char c);
#endif