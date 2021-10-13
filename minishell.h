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
char	**ft_flex(char const *s, char c);
char	**split_pipe(char *line, t_headers *header);
void	envi(char **env, t_headers *header);
void	check_error(char *line);
void	*ft_free(char **p);
void	ft_delbottom(t_headers *head);
void	ft_addbottom(t_headers *head, char *var, char *val);
char	*add_str(char *str);
void	save_cmd(t_headers *header, char **str);
#endif
