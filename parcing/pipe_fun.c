/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:05:19 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/11 14:08:24 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	set_char(char *str, int a, int b)
{
	char	c;

	c = 0;
	if (str[a] == '"' || str[a] == 39)
	{
		if (b == 1)
			c = str[a];
	}
	return (c);
}

int	left_check(char *str, int a)
{
	int		b;
	char	c;

	b = 1;
	while (a >= 0)
	{
		c = set_char(str, a, b);
		while (c != 0 && a >= 0)
		{
			b = 0;
			a--;
			if (a >= 0 && str[a] == c)
			{
				b = 1;
				break ;
			}
		}
		if (a == 0)
			break ;
		a--;
	}
	return (b);
}

int	valid_pipe(char *str, int c)
{
	int	a;
	int	b;

	b = 0;
	a = c;
	while (str[a])
	{
		if (str[a] == '|')
			b = left_check(str, a);
		if (b == 1)
			break ;
		a++;
	}
	return (a);
}

void	valid_pipes(t_mini *mini)
{
	int	a;

	a = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[0][a] == '|' && serach_quote(mini, a) == 1)
			mini->temp[1][a] = 'P';
		a++;
	}
}
