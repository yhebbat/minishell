/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:03:15 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 04:07:53 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_herdocs_rl(char	*limiter, int fd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handle_sigint_herdoc);
		line = readline("heredoc>");
		if (!line)
		{
			__get_var(SETEXIT, 0);
			exit(0);
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			__get_var(SETEXIT, 0);
			exit(0);
		}
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
}

char	*ft_herdocs(char *str)
{
	char	*limiter;
	int		pid;
	char	*name;
	int		fd;
	int		status;

	limiter = findredtosave(str);
	name = ft_strjoin("/tmp/", limiter);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	__get_var(SETPID, -1);
	pid = fork();
	if (pid == 0)
		ft_herdocs_rl(limiter, fd);
	waitpid(pid, &status, 0);
	if (status == 256)
		__get_var(SETEXIT, 1);
	__get_var(SETPID, 0);
	free(limiter);
	close(fd);
	return (name);
}

void	check_redquotes(int	*s_q, int *d_q, char c)
{
	if (c == '\'')
		(*s_q)++;
	if (c == '"')
		(*d_q)++;
}

int	file_is_here(t_cmds *find_redirection, int *red, int *i)
{
	char	*var;
	char	*val;
	char	*rest;

	var = find_red(find_redirection->cmd, *i, red);
	rest = ft_strdup(ft_strstr(find_redirection->cmd + (*i), var));
	if (*red == 4)
		val = ft_herdocs(var);
	else
		val = findredtosave(var);
	find_redirection->cmd = ft_strjoin_redfree(find_redirection->cmd, rest, *i);
	ft_addbotfile(find_redirection, val, *red);
	(*i) = -1;
	free(var);
	free(val);
	free(rest);
	if (__get_var(GETEXIT, 0) == 1 && *red == 4)
		return (1);
	return (0);
}

int	checkredirection_cmd(t_cmds	*find_red)
{
	int	red;
	int	s_q;
	int	d_q;
	int	i;

	while (find_red)
	{
		i = -1;
		red = 0;
		s_q = 0;
		d_q = 0;
		while (find_red->cmd[++i])
		{
			check_redquotes(&s_q, &d_q, find_red->cmd[i]);
			if ((find_red->cmd[i] == '>' || find_red->cmd[i] == '<')
				&& !(d_q % 2) && !(s_q % 2))
			{
				if (file_is_here(find_red, &red, &i))
					return (-1);
			}
		}
		find_red = find_red->next;
	}
	return (1);
}
