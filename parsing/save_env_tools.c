/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:56:06 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:56:07 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delbottom_helper(t_env *to_delete)
{
	if (to_delete->val != NULL)
		free(to_delete->val);
	if (to_delete->var != NULL)
		free(to_delete->var);
}

void	ft_delbottom(t_headers *head)
{
	t_env	*to_delete;
	t_env	*stack;

	if (head != NULL && head->env_h != NULL)
	{
		to_delete = head->env_f;
		if (!to_delete->preced)
		{
			ft_delbottom_helper(to_delete);
			free(to_delete);
			head->env_h = NULL;
			head->env_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->preced;
			head->env_f = stack;
			stack->suivant = NULL;
			ft_delbottom_helper(to_delete);
			free(to_delete);
			to_delete = NULL;
		}
	}
}
