/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 04:04:14 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 04:07:58 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_redfree(char *s1, char *s2, int i)
{
	char	*ret;

	ret = ft_strjoin_red(s1, s2, i);
	free (s1);
	return (ret);
}

char	*ft_herdocs_rl_helper(char *ret, char *line)
{
	if (ret == NULL)
	{
		ret = ft_strdup(line);
		ret = ft_strjoin_free(ret, "\n");
	}
	else
	{
		ret = ft_strjoin_free(ret, line);
		ret = ft_strjoin_free(ret, "\n");
	}
	free(line);
	return (ret);
}

void	handle_sigint_herdoc(int sigint)
{
	(void)sigint;
	write(1, "\n", 1);
	__get_var(SETEXIT, 1);
	exit(1);
}
