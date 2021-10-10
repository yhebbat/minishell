#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*suivant;
	struct s_env	*preced;
}t_env;

typedef	struct	s_file
{
	char	*filename;
	int		type;
	struct	t_file	*next; 
}t_file;

typedef struct s_cmds
{
	// redirections;
	char	**args;
	int		d_q;
	int		s_q;
	char	*cmd;
	struct	t_file	*file;
	struct	s_cmds	*next;
	struct	s_cmds	*prec;
}t_cmds;


typedef struct s_headers
{
	struct s_env	*env_h;
	struct s_env	*env_f;
	struct s_cmds	*cmd_h;
	struct s_cmds	*cmd_f;
}t_headers;

char	**ft_split(char const *s, char c);
char	**ft_toke(char const *s, char c);
#endif
