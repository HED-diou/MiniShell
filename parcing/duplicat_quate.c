/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicat_quate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:57:51 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/08 12:22:19 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	serach_quote(t_mini *mini, int a)
{
	while (mini->temp[0][a])
	{
		if (mini->temp[1][a] == '>' || mini->temp[1][a] == ')')
			return (0);
		if (mini->temp[1][a] == '<' || mini->temp[1][a] == '(')
			return (1);
		a++;
	}
	return (1);
}

void	str_flag(char **str, int a, int i, char c)
{
	char	e;
	char	d;

	if (c == 39)
	{
		e = '<';
		d = '>';
	}
	if (c == '"')
	{
		e = '(';
		d = ')';
	}
	(*str)[i] = e;
	(*str)[a] = d;
}

int	flag_utils(t_mini *mini, int a, int i, char c)
{
	a++;
	while (mini->temp[0][a])
	{
		if (mini->temp[0][a] == c)
		{
			str_flag(&(mini->temp[1]), a, i, c);
			return (a);
		}
		a++;
	}
	return (-1);
}

char	set_c(t_mini *mini, int a)
{
	char	c;

	c = mini->temp[0][a];
	if (c == '"')
		mini->temp[1][a] = '3';
	if (c == 39)
		mini->temp[1][a] = '4';
	return (c);
}

void	flag_quotes(t_mini *mini, int a, int i)
{
	int		b;
	char	c;

	b = 1;
	while (mini->temp[0][a])
	{
		if (mini->temp[0][a] == '"' || mini->temp[0][a] == 39)
		{
			if (b == 1)
			{
				i = a;
				c = set_c(mini, a);
			}
			b = flag_utils(mini, a, i, c);
			if (b != -1)
			{
				a = b;
				b = 1;
			}
			else
				break ;
		}
		a++;
	}
}
