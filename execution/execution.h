/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:30 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 03:26:23 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <sys/types.h>
# include <sys/errno.h>
# include <limits.h>

typedef struct s_exec
{
	char	**path;
	char	**env;
	int		*fd;
	int		in;
	int		i;
	int		*pid;
	int		nb_cmd;
}t_exec;

int		g_exit_status;

t_env	*find_var_env(char *str, t_env *env);
void	ft_env(t_exec *exec);
void	cd(t_cmds *cmd, t_headers *header);
int		execute(t_headers *header);
void	pwd(t_cmds *cmd);
void	echo(t_cmds *cmd);
void	export(t_cmds *cmd, t_exec *exec, t_headers *header);
void	unset(t_cmds *cmd, t_exec *exec, t_headers *header);
int		ft_exit(t_cmds *cmd);
void	ft_pipe(t_cmds *cmd, t_exec *exec);
void	ft_pipe_last(t_cmds *cmd, t_exec *exec);
void	fill_env(t_exec *exec, t_headers *header);
void	fill_env2(t_exec *exec, t_headers *header);
void	ft_perror(char *c, char *s);
void	redirection(t_cmds *cmd_h, t_exec *exec);
void	half_exec_init(t_exec *exec, t_cmds **cmd);
void	exec_init(t_headers *header, t_exec *exec);
void	exec_free(t_exec *exec);
void	join_path(t_exec *exec, t_cmds **cmd);
void	replace_arg(t_headers *header, t_exec *exec);
void	ft_more_cmd(t_cmds *cmd, t_exec *exec);
void	print_error(t_cmds *cmd, char *s, int i);
void	child_proccess(t_cmds *cmd, t_exec *exec);
void	one_command(t_cmds *cmd, t_exec *exec);
void	ft_execve(t_cmds *cmd, t_exec *exec);
void	check_builtins_execve(t_cmds *cmd, t_exec *exec, t_headers *header);
void	dup_n_close(int out, int in);
void	check_builtins_condition(t_cmds *cmd, t_exec *exec, t_headers *header);
void	check_builtins(t_cmds *cmd, t_exec *exec, t_headers *header);
int		is_builtin(t_cmds *cmd, t_exec *exec, t_headers *header);
void	ft_cmds(t_exec *exec, t_cmds **cmd, t_headers *header);
void	ft_simple_cmd(t_exec *exec, t_cmds *cmd, t_headers *header);
void	ft_last_cmd(t_exec *exec, t_cmds *cmd, t_headers *header);
t_cmds	*commands(t_exec *exec, t_cmds *cmd, t_headers *header);
void	some_status_code(t_cmds *cmd, int *stat);
int		ft_isdigit(int c);
void	ft_error(char *c);
int		set_eq(char *str, int *eq, int *i);
char	*check_eq(char *str, int *eq);
char	*fill_exportval(char *str, int *eq);
void	only_export(t_cmds *cmd, t_env *env);
void	add_to_export(t_cmds *cmd, t_env *env, t_headers *header, int t);
void	unvalid_unset(t_cmds *cmd, int t);
#endif
