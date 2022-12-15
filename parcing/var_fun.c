/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 00:24:57 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/08 12:25:22 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_par(t_mini *par, char *str)
{
	int	b;
	int	a;

	a = 0;
	b = ft_strlen(str) + 4;
	par->temp = malloc(sizeof(char *) * 4);
	par->temp[0] = malloc(b);
	par->temp[1] = malloc(b);
	par->temp[2] = malloc(b);
	while (str[a])
	{
		par->temp[0][a] = str[a];
		par->temp[1][a] = '0';
		par->temp[2][a] = '0';
		a++;
	}
	a = b - 4;
	while (a < b)
	{
		par->temp[0][a] = 0;
		par->temp[1][a] = 0;
		par->temp[2][a] = 0;
		a++;
	}
}

void	delete_quote(t_mini *var, char **str)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while ((*str)[a])
	{
		if (var->temp[1][a] == '<' || var->temp[1][a] == '('
				|| var->temp[1][a] == ')' || var->temp[1][a] == '>')
		{
			b = a;
			while (var->temp[1][b])
			{
				(*str)[b] = (*str)[b + 1];
				var->temp[1][b] = var->temp[1][b + 1];
				b++;
			}
			(*str)[b] = 0;
			var->temp[1][b] = 0;
			a--;
		}
		a++;
	}
}
