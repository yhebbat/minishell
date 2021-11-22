/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 03:38:03 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/22 03:38:06 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "execution.h"

void	ft_env(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->env[i])
	{
		printf("%s\n", exec->env[i]);
		i++;
	}
	__get_var(SETEXIT, 0);
}
