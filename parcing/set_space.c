/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:05:45 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/08 11:58:53 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_double(t_mini *mini, int a)
{
	while (mini->temp[1][a] && mini->temp[1][a] != '>')
	{
		if (is_space(mini->temp[0][a]) == 0)
			mini->temp[1][a] = '1';
		a++;
	}
	return (a);
}

int	search_single(t_mini *mini, int a)
{
	while (mini->temp[1][a] && mini->temp[1][a] != ')')
	{
		if (is_space(mini->temp[0][a]) == 0)
			mini->temp[1][a] = '1';
		a++;
	}
	return (a);
}

void	set_space_q(t_mini *mini)
{
	int	a;

	a = 0;
	while (mini->temp[1][a])
	{
		if (mini->temp[1][a] == '<')
			a = search_double(mini, a);
		else if (mini->temp[1][a] == '(')
			a = search_single(mini, a);
		a++;
	}
}

void	set_space(t_mini *mini)
{
	int	a;

	a = 0;
	set_space_q(mini);
	while (mini->temp[1][a])
	{
		if (is_space(mini->temp[0][a]) == 0 && mini->temp[1][a] != '1')
			mini->temp[1][a] = '2';
		a++;
	}
}
