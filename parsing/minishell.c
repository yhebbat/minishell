/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:03:06 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 03:52:36 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse(char *line, t_headers *header)
{
	char	**str;

	if (!check_error(line))
	{
		str = split_pipe(line, header);
		save_cmd(header, str);
		ft_free(str);
	}
}

void	handle_sigint(int sigint)
{
	(void)sigint;
	if (__get_var(GETPID, 0) == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		__get_var(SETEXIT, 1);
	}
}

int	__get_var(t_norm op, int value)
{
	static int		exit_status = 0;
	static int		pids = 0;

	if (op == GETEXIT)
		return (exit_status);
	if (op == SETEXIT)
		exit_status = value;
	if (op == SETPID)
		pids = value;
	if (op == GETPID)
		return (pids);
	return (0);
}

void	ft_readline(t_headers *header)
{
	char		*line;
	int			k;

	k = 1;
	line = NULL;
	while (k)
	{
		line = readline("minishell🔥\%");
		if (!line)
		{
			printf("exit\n");
			while (header->env_h != NULL)
				ft_delbottom(header);
			free(header);
			header = NULL;
			exit(__get_var(GETEXIT, 0));
		}
		parse(line, header);
		add_history(line);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_headers	*header;

	(void) ac;
	(void) av;
	__get_var(SETPID, 0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	header = malloc(sizeof(t_headers));
	header->env_h = NULL;
	header->env_f = NULL;
	header->cmd_h = NULL;
	envi(env, header);
	ft_readline(header);
	while (header->env_h != NULL)
		ft_delbottom(header);
	free(header);
	header = NULL;
}
