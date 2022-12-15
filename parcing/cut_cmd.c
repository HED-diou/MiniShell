/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:56:35 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/07 19:46:35 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_cmd(t_mini *mini, int a)
{
	int	b;

	b = 0;
	while (mini->temp[1][a] == '1' || mini->temp[1][a] == '0' ||
			mini->temp[1][a] == '<' || mini->temp[1][a] == '>' ||
			mini->temp[1][a] == '(' || mini->temp[1][a] == ')' ||
			mini->temp[1][a] == 'V' || mini->temp[1][a] == 'W' ||
			mini->temp[1][a] == 'U')
	{
		ft_realloc(&mini->cmd, 1);
		mini->cmd[b++] = mini->temp[0][a];
		mini->temp[2][a++] = 'T';
	}
	mini->cmd[b] = '\0';
}

void	get_simple_cmd(t_mini *mini)
{
	int	a;

	a = 0;
	mini->cmd = NULL;
	while (mini->temp[0][a])
	{
		if (mini->temp[2][a] != 'T' && (mini->temp[1][a] == '1' ||
				mini->temp[1][a] == '0' || mini->temp[1][a] == '<' ||
				mini->temp[1][a] == '>' || mini->temp[1][a] == '(' ||
				mini->temp[1][a] == ')' || mini->temp[1][a] == 'V' ||
				mini->temp[1][a] == 'W' || mini->temp[1][a] == 'U'))
		{
			get_cmd(mini, a);
			break ;
		}
		a++;
	}
}

int	count_options(t_mini *mini)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	c = 0;
	while (mini->temp[0][a])
	{
		b = -1;
		while (mini->temp[2][a] != 'T' && (mini->temp[1][a] == '1' ||
				mini->temp[1][a] == '0' || mini->temp[1][a] == '<' ||
				mini->temp[1][a] == '>' || mini->temp[1][a] == '(' ||
				mini->temp[1][a] == ')' || mini->temp[1][a] == 'V' ||
				mini->temp[1][a] == 'W' || mini->temp[1][a] == 'U'))
		{
			a++;
			b = a;
		}
		if (a == b)
			c++;
		if (b == -1)
			a++;
	}
	return (c);
}

int	get_option(t_mini *mini, int a, int c)
{
	int	b;

	b = 0;
	while (mini->temp[1][a] == '1' || mini->temp[1][a] == '0' ||
			mini->temp[1][a] == '<' || mini->temp[1][a] == '>' ||
			mini->temp[1][a] == '(' || mini->temp[1][a] == ')' ||
			mini->temp[1][a] == 'V' || mini->temp[1][a] == 'W' ||
			mini->temp[1][a] == 'U')
	{
		ft_realloc(&mini->option[c], 1);
		mini->option[c][b++] = mini->temp[0][a];
		mini->temp[2][a++] = 'T';
	}
	mini->option[c][b] = '\0';
	return (a - 1);
}

void	get_simple_option(t_mini *mini)
{
	int	a;
	int	b;
	int	c;

	b = count_options(mini);
	a = 0;
	c = -1;
	mini->option = (char **)malloc(sizeof(char *) * (b + 2));
	while (a <= b)
		mini->option[a++] = NULL;
	a = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[2][a] != 'T' && (mini->temp[1][a] == '1' ||
				mini->temp[1][a] == '0' || mini->temp[1][a] == '<' ||
				mini->temp[1][a] == '>' || mini->temp[1][a] == '(' ||
				mini->temp[1][a] == ')' || mini->temp[1][a] == 'V' ||
				mini->temp[1][a] == 'W' || mini->temp[1][a] == 'U'))
			a = get_option(mini, a, ++c);
		a++;
	}
}
