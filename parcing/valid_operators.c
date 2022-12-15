/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 03:59:46 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/09 11:08:49 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	valid_normal_input(t_mini *mini)
{
	int	a;

	a = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[0][a] == '<' && mini->temp[1][a] != 'h'
				&& serach_quote(mini, a) == 1)
			mini->temp[1][a] = '9';
		a++;
	}
}

void	valid_normal_output(t_mini *mini)
{
	int	a;

	a = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[0][a] == '>' && mini->temp[1][a] != '8' &&
				serach_quote(mini, a) == 1)
			mini->temp[1][a] = '7';
		a++;
	}
}

void	valid_herdog(t_mini *mini)
{
	int	a;

	a = 0;
	ft_realloc(&mini->temp[0], 2);
	while (mini->temp[0][a + 1])
	{
		if (mini->temp[1][a] == '9')
			a++;
		else if (mini->temp[0][a] == '<' && mini->temp[0][a + 1] == '<'
				&& serach_quote(mini, a) == 1)
		{
			mini->temp[1][a] = 'h';
			mini->temp[1][a + 1] = 'h';
			a++;
		}
		a++;
	}
}

void	valid_cat_outpu(t_mini *mini)
{
	int	a;

	a = 0;
	ft_realloc(&mini->temp[0], 2);
	while (mini->temp[0][a + 1])
	{
		if (mini->temp[1][a] == '7')
			a++;
		if (mini->temp[0][a] == '>' && mini->temp[0][a + 1] == '>'
				&& serach_quote(mini, a) == 1)
		{
			mini->temp[1][a] = '8';
			mini->temp[1][a + 1] = '8';
			a++;
		}
		a++;
	}
}

void	valid_opertors(t_mini *mini)
{
	valid_cat_outpu(mini);
	valid_herdog(mini);
	valid_normal_output(mini);
	valid_normal_input(mini);
	valid_pipes(mini);
	valid_var(mini);
}
