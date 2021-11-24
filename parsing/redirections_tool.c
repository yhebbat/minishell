/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 04:04:16 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 04:06:25 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_it(char *str, int *i, int r)
{
	while (str[r] == '>' || str[r] == '<' || str[r] == ' ')
		laysameh(&r, i);
	while (str[r] && str[r] != ' ' && str[r] != '>' && str[r] != '<')
	{
		if (str[r] == '"')
		{
			laysameh(&r, i);
			while (str[r] && str[r] != '"')
				laysameh(&r, i);
			laysameh(&r, i);
		}
		else if (str[r] == '\'')
		{
			laysameh(&r, i);
			while (str[r] && str[r] != '\'')
				laysameh(&r, i);
			laysameh(&r, i);
		}
		else
			laysameh(&r, i);
	}
}

char	*find_red(char *str, int k, int *red)
{
	int		i;
	int		r;
	char	*var;

	i = 0;
	r = k;
	type_of_red(str, r, red);
	skip_it(str, &i, r);
	var = malloc(sizeof(char) * (i + 1));
	r = i;
	i = 0;
	while (i < r)
		var[i++] = str[k++];
	var[i] = '\0';
	return (var);
}

void	findredtosave_help(char	*var, int *k, int *i)
{
	if (var[*i] == '"')
	{
		(*i)++;
		while (var[*i] && var[*i] != '"')
		{
			(*k)++;
			(*i)++;
		}
		(*i)++;
	}
	else if (var[*i] == '\'')
	{
		(*i)++;
		while (var[*i] && var[*i] != '\'')
		{
			(*k)++;
			(*i)++;
		}
		(*i)++;
	}
	else
	{
		(*i)++;
		(*k)++;
	}
}

char	*findredtosave_help2(char *var, int *k, int t)
{
	char	*ret;

	ret = malloc(sizeof(char) * ((*k) + 1));
	*k = 0;
	while (var[t] && var[t] != '>' && var[t] != '<' && var[t] != ' ')
	{
		if (var[t] == '\'')
		{
			t++;
			while (var[t] != '\'')
				ret[(*k)++] = var[t++];
			t++;
		}
		else if (var[t] == '"')
		{
			t++;
			while (var[t] != '"')
				ret[(*k)++] = var[t++];
			t++;
		}
		else
			ret[(*k)++] = var[t++];
	}
	ret[*k] = '\0';
	return (ret);
}

char	*findredtosave(char *var)
{
	int		i;
	int		k;
	int		t;

	k = 0;
	t = 0;
	i = 0;
	while (var[i] == '>' || var[i] == '<' || var[i] == ' ')
		var++;
	while (var[i] && var[i] != '>' && var[i] != '<' && var[i] != ' ')
		findredtosave_help(var, &k, &i);
	return (findredtosave_help2(var, &k, t));
}
