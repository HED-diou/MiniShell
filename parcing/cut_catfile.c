/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_catfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:56:15 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/09 17:00:58 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_normal_output(t_mini *mini, int a, int b, char t)
{
	int	c;

	c = 0;
	a++;
	while (mini->temp[0][a] && mini->temp[1][a] == '2')
		a++;
	while (mini->temp[0][a] && mini->temp[1][a] != '2' &&
			mini->temp[1][a] != '7' && mini->temp[1][a] != '9' &&
			mini->temp[1][a] != 'h' && mini->temp[1][a] != '8')
	{
		ft_realloc(&(mini->rederct[b]), 1);
		mini->rederct[b][c++] = mini->temp[0][a];
		mini->temp[2][a++] = 'T';
	}
	ft_realloc(&(mini->rederct[b]), 3);
	mini->rederct[b][c++] = ' ';
	mini->rederct[b][c++] = t;
	mini->rederct[b][c] = '\0';
	return (a - 1);
}

int	get_comli_output(t_mini *mini, int a, int b)
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
		ft_realloc(&(mini->rederct[b]), 1);
		mini->rederct[b][c++] = mini->temp[0][a];
		mini->temp[2][a++] = 'T';
	}
	ft_realloc(&(mini->rederct[b]), 3);
	mini->rederct[b][c++] = ' ';
	mini->rederct[b][c++] = 'c';
	mini->rederct[b][c] = 0;
	return (a - 1);
}

int	count_them_3(t_mini *mini)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[1][a] == '7')
			b++;
		else if (mini->temp[1][a] == '9')
			b++;
		else if (mini->temp[1][a] == '8')
		{
			b++;
			a++;
		}
		a++;
	}
	return (b);
}

void	get_simple_catfile(t_mini *mini)
{
	int	a;
	int	b;
	int	s;

	b = -1;
	a = 0;
	s = count_them_3(mini) + 1;
	mini->rederct = malloc(sizeof(char *) * (s + 1));
	while (a <= s)
		mini->rederct[a++] = NULL;
	a = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[1][a] == '8')
			a = get_comli_output(mini, a, ++b);
		else if (mini->temp[1][a] == '7')
			a = get_normal_output(mini, a, ++b, 'o');
		else if (mini->temp[1][a] == '9')
			a = get_normal_output(mini, a, ++b, 'x');
		a++;
	}
}
