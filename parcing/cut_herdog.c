/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_herdog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:56:48 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/09 11:36:07 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_herdog(t_mini *mini, int a, int b)
{
	int	c;

	c = 0;
	a += 2;
	while (mini->temp[0][a] && mini->temp[1][a] == '2')
		a++;
	while (mini->temp[0][a] && mini->temp[1][a] != '2' &&
			mini->temp[1][a] != '7' && mini->temp[1][a] != '9' &&
			mini->temp[1][a] != 'h' && mini->temp[1][a] != '8')
	{
		ft_realloc(&(mini->herdog[b]), 1);
		mini->herdog[b][c++] = mini->temp[0][a];
		mini->temp[2][a++] = 'T';
	}
	ft_realloc(&(mini->herdog[b]), 1);
	mini->herdog[b][c] = '\0';
	return (a - 1);
}

int	count_them_2(t_mini *mini)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[1][a] == 'h')
		{
			b++;
			a++;
		}
		a++;
	}
	return (b);
}

void	get_simple_herdog(t_mini *mini)
{
	int	a;
	int	b;
	int	s;

	b = -1;
	a = 0;
	s = count_them_2(mini) + 3;
	mini->herdog = malloc(sizeof(char *) * (s + 1));
	while (a <= s)
		mini->herdog[a++] = NULL;
	a = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[1][a] == 'h')
			a = get_herdog(mini, a, ++b);
		a++;
	}
}
