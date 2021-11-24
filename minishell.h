/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:50:44 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 04:08:34 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include  <errno.h>
# include <fcntl.h>
# include <sys/stat.h>

# define ONE 1
# define TWO 2
# define ONEREV 3
# define TWOREV 4

typedef struct s_toke
{
	int	i;
	int	j;
	int	k;
}t_toke;

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*suivant;
	struct s_env	*preced;
}t_env;

typedef struct s_file
{
	char			*filename;
	int				type;
	struct s_file	*next;
	struct s_file	*prec;
}t_file;

typedef struct s_cmds
{
	char			**args;
	char			*path;
	char			*cmd;
	struct s_file	*file_h;
	struct s_file	*file_f;
	struct s_cmds	*next;
	struct s_cmds	*prec;
}t_cmds;

typedef struct s_headers
{
	struct s_env	*env_h;
	struct s_env	*env_f;
	struct s_cmds	*cmd_h;
	struct s_cmds	*cmd_f;
}t_headers;

int		g_pids;

typedef enum e_norm
{
	GETEXIT,
	SETEXIT,
	GETPID,
	SETPID
}t_norm;

int		ft_isalpha(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strdup_free(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strstr(char *src, char *tofind);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_strlen(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin_dollar(char *s1, char *s2, int i);
char	*ft_strjoin_red(char *s1, char *s2, int i);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_dollarfree(char *s1, char *s2, int i);
void	envi(char **env, t_headers *header);
void	ft_delbottom(t_headers *head);
void	ft_addbottom(t_headers *head, char *var, char *val);
int		check_error(char *line);
int		nb_of_quotes(char *line);
int		check_error_pipes(char *line);
int		check_error_redirections(char *line);
char	**ft_toke(char const *s, char c);
char	**ft_flex(char const *s, char c);
char	**split_pipe(char *line, t_headers *header);
void	*ft_free(char **p);
void	save_cmd(t_headers *header, char **str);
void	ft_addbotfile(t_cmds *head, char *val, int type);
void	ft_delbotfile(t_cmds *head);
int		checkredirection_cmd(t_cmds	*find_redirection);
void	fill_cmd(t_headers *header, char	**str);
void	ft_delbotcmd(t_headers *head);
int		execute(t_headers *header);
void	laysameh(int *r, int *i);
int		__get_var(t_norm op, int value);
int		print_check_error(char *str);
void	nb_of_dq(char *line, int *d_q, int *i);
void	nb_of_sq(char *line, int *s_q, int *i);
int		nb_of_quotes(char *line);
int		check_space(char *line, int i);
void	ft_addbotcmd_help(t_cmds *to_add);
void	ft_addbotcmd(t_headers *head, char *val);
void	ft_freefile(t_cmds *head);
void	ft_delbotcmd_help(t_cmds *to_delete);
void	ft_complet(t_headers *header);
void	fill_cmd(t_headers *header, char **str);
char	*to_find(char *str, int k);
int		ft_intlen(unsigned int nb);
char	*ft_itoa(int c);
char	*print_exitstat(char *str, char *var);
char	*findit(t_headers *header, char *var);
int		calculate_dollar(char *str, int i);
void	check_dollarquotes(int *s_q, int *d_q, char c);
void	dollar_is_here(t_cmds *new_cmd, int *i, t_headers *header);
void	ft_mmots_helper(char const *s, int	*i);
void	ft_rempp_helper2(t_toke *toke, char **p, char const *s);
void	ft_rempp_helper(t_toke *toke, char **p, char const *s);
void	ft_deltop_helper(t_env *to_delete);
void	ft_deltop(t_headers *head);
void	ft_addtop(t_headers *head, char *var, char *val);
void	ft_mots_helper(char const *s, int	*i);
void	laysameh(int *r, int *i);
void	ft_remp_helper2(t_toke *toke, char **p, char const *s);
void	ft_remp_helper(t_toke *toke, char **p, char const *s);
char	**split_pipe(char *line, t_headers *header);
void	ft_addbotfile_helper(t_file	*to_add, char *val);
void	ft_addbotfile(t_cmds *head, char *val, int type);
void	ft_delbotfile(t_cmds *head);
int		redcounter(char *str, int i);
void	type_of_red(char *str, int r, int *red);
void	skip_it(char *str, int *i, int r);
char	*find_red(char *str, int k, int *red);
void	findredtosave_help(char	*var, int *k, int *i);
char	*findredtosave_help2(char *var, int *k, int t);
char	*findredtosave(char *var);
char	*ft_strjoin_redfree(char *s1, char *s2, int i);
char	*ft_herdocs_rl_helper(char *ret, char *line);
void	handle_sigint_herdoc(int sigint);
#endif