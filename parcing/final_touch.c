/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_touch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:59:06 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/10 15:01:05 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	strs_expand(char **str, t_env *env)
{
	int	a;

	a = 0;
	while (str[a])
	{
		simple_all(&str[a], env);
		a++;
	}
}

void	expand_all_vars(t_mini **mini, t_env *env)
{
	t_mini	*temp;

	temp = *mini;
	while (temp)
	{
		simple_all(&temp->cmd, env);
		strs_expand(temp->option, env);
		strs_expand(temp->herdog, env);
		strs_expand(temp->rederct, env);
		temp = temp->next;
	}
}

void	empty_herdoc(t_mini *mini, t_env *env)
{
	t_mini	*lst;

	lst = NULL;
	fill_list(&mini->temp[0], &lst, NULL);
	excute_hedoc_2(lst, env);
	free_list(&lst);
}
