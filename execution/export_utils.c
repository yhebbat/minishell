/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:09:08 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:09:09 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_error(char *c)
{
	write(2, "export: `", 9);
	write(2, c, ft_strlen(c));
	write(2, "': not a valid identifier\n", 27);
}

int	set_eq(char *str, int *eq, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '+' && str[*i + 1] != '=')
		{
			*eq = -1;
			ft_error(str);
			__get_var(SETEXIT, 1);
			break ;
		}
		else if (str[*i] == '+' && str[*i + 1] == '=')
		{
			*eq = 2;
			break ;
		}
		else if (str[*i] == '=')
		{
			*eq = 1;
			break ;
		}
		(*i)++;
		*eq = 0;
	}
	return (*i);
}

char	*check_eq(char *str, int *eq)
{
	int		i;
	int		k;
	char	*ret;

	ret = NULL;
	k = 0;
	i = 0;
	set_eq(str, eq, &i);
	if (*eq == 0 || *eq == -1)
		ret = ft_strdup(str);
	else if (*eq == 2 || *eq == 1)
	{
		ret = malloc(sizeof(char) * (i + 1));
		if (!ret)
			return (0);
		while (str[k] && k < i)
		{
			ret[k] = str[k];
			k++;
		}
		ret[k] = '\0';
	}
	return (ret);
}

char	*fill_exportval(char *str, int *eq)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] != '=')
			break ;
		else if (str[i] == '+' && str[i + 1] == '=')
			break ;
		else if (str[i] == '=')
			break ;
		i++;
	}
	if (*eq == 0 || *eq == -1)
		ret = NULL;
	else if (*eq == 1 || *eq == 2)
		ret = ft_strdup(&str[i + *eq]);
	return (ret);
}

t_env	*find_var_env(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->var) == 0)
			return (env);
		env = env->suivant;
	}
	return (NULL);
}
