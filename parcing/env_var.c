/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:58:06 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/08 09:51:55 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_quote_var(t_mini *mini, int a)
{
	a++;
	while (mini->temp[0][a])
	{
		if (mini->temp[1][a] == '>')
			return (1);
		if (mini->temp[1][a] == '(' || mini->temp[1][a] == ')' ||
				mini->temp[1][a] == '<')
			return (0);
		a++;
	}
	return (0);
}

void	valid_var(t_mini *mini)
{
	int	a;

	a = 0;
	while (mini->temp[1][a])
	{
		if (mini->temp[0][a] == '$' && mini->temp[1][a + 1] == '0' &&
				search_quote_var(mini, a) == 1)
			mini->temp[1][a++] = 'W';
		if (mini->temp[0][a] == '$' && mini->temp[1][a + 1] == '0' &&
				search_quote_var(mini, a) == 0 && mini->temp[0][a + 1] != '$')
			mini->temp[1][a++] = 'V';
		a++;
	}
}
