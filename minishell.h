#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

// 1 -> >
// 2 -> >>
// 3 -> <
// 4 -> <<

# define ONE 1
# define TWO 2
# define ONEREV 3
# define TWOREV 4

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
	struct	s_file	*next; 
	struct	s_file	*prec; 
}t_file;

typedef struct s_cmds
{
	// redirections;
	char	**args;
	char	*cmd;
	struct	s_file	*file_h;
	struct	s_file	*file_f;
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
int		check_error(char *line);
void	*ft_free(char **p);
void	ft_delbottom(t_headers *head);
void	ft_addbottom(t_headers *head, char *var, char *val);
char	*add_str(char *str);
void	save_cmd(t_headers *header, char **str);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_dollar(char *s1, char *s2, int i);
char	*ft_strdup(const char *s);
void	ft_addbotfile(t_cmds *head, char *val, int type);
void	ft_delbotfile(t_cmds *head);
void	checkredirection_cmd(t_headers *header);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strjoin_red(char *s1, char *s2, int i);
char	*ft_strstr(const char *src, const char *tofind);
#endif
