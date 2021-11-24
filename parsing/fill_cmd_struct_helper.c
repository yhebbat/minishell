/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_struct_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:44:46 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:44:47 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_complet(t_headers *header)
{
	t_cmds	*new_cmd;

	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		new_cmd->args = ft_flex(new_cmd->cmd, ' ');
		new_cmd = new_cmd->next;
	}
}

void	fill_cmd(t_headers *header, char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_addbotcmd(header, str[i]);
		i++;
	}
}

char	*to_find(char *str, int k)
{
	int		i;
	int		r;
	char	*var;

	i = 0;
	r = k + 1;
	while (str[r] && str[r] != '"' && str[r] != ' '
		&& str[r] != '\'' && str[r] != '$' && str[r] != '=')
	{
		i++;
		r++;
	}
	var = malloc(sizeof(char) * (i + 2));
	r = i + 1;
	i = 0;
	while (i < r)
		var[i++] = str[k++];
	var[i] = '\0';
	return (var);
}

int	ft_intlen(unsigned int nb)
{
	int	i;

	i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int c)
{
	unsigned int	nb;
	unsigned int	i;
	char			*str;

	nb = c;
	i = 0;
	if (c <= 0)
	{
		nb = -c;
		i = 1;
	}
	i += ft_intlen(nb);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (0);
	str[i] = '\0';
	while (i-- > 0)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (c < 0)
		str[0] = '-';
	return (str);
}
