/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:51:46 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/10 20:22:05 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_next_normal(t_mini *mini, int a)
{
	int	b;

	b = a;
	a++;
	while (mini->temp[1][a] && mini->temp[1][a] == '2')
		a++;
	if (mini->temp[1][a] == '0' || mini->temp[1][a] == '<' ||
			mini->temp[1][a] == '(' || mini->temp[1][a] == 'V' ||
			mini->temp[1][a] == 'W')
		return (a);
	else if (mini->temp[1][a] == 0)
		printf("syntax error near unexpected token `newline'\n");
	else
		printf("syntax error near unexpected token %c\n", mini->temp[0][a]);
	mini->temp[0][b] = 0;
	return (-1);
}

int	check_next_double(t_mini *mini, int a)
{
	int	b;

	b = a;
	a += 2;
	while (mini->temp[1][a] && mini->temp[1][a] == '2')
		a++;
	if (mini->temp[1][a] == '0' || mini->temp[1][a] == '<' ||
			mini->temp[1][a] == '(' || mini->temp[1][a] == 'V' ||
			mini->temp[1][a] == 'W')
		return (a);
	else if (mini->temp[1][a] == 0)
		printf("syntax error near unexpected token `newline'\n");
	else
		printf("syntax error near unexpected token %c\n", mini->temp[0][a]);
	mini->temp[0][b] = '\0';
	return (-1);
}

int	check_first(void)
{
	printf("syntax error near unexpected token `|'\n");
	return (-1);
}

int	check_pipe(t_mini *mini, int a)
{
	int	b;

	b = a;
	a++;
	while (mini->temp[1][a] && mini->temp[1][a] == '2')
		a++;
	if (mini->temp[1][a] == 'P')
	{
		printf("syntax error near unexpected token `|'\n");
		mini->temp[0][b] = 0;
		return (-1);
	}
	return (a);
}

int	check_errors(t_mini *mini)
{
	int	a;

	a = 0;
	while (mini->temp && mini->temp[1][a])
	{
		if (mini->temp[1][a] == '9' || mini->temp[1][a] == '7')
			a = check_next_normal(mini, a);
		else if (mini->temp[1][a] == '8' || mini->temp[1][a] == 'h')
			a = check_next_double(mini, a);
		else if (a == 0 && mini->temp[1][a] == 'P')
			a = check_first();
		else if (mini->temp[1][a] == 'P')
			a = check_pipe(mini, a);
		else if (a == -1)
			return (0);
		else
			a++;
	}
	return (1);
}
