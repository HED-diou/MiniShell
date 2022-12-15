/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:19:40 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/08 12:16:34 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_struct(t_mini *struc, char *str)
{
	fill_par(struc, str);
	flag_quotes(struc, 0, 0);
	set_space(struc);
	valid_opertors(struc);
}

void	search_str(t_mini *var, char *s2, int *a, int *b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!var->temp[0] || !s2)
		return ;
	while (var->temp[0][i])
	{
		j = 0;
		while (var->temp[0][i + j] && s2[j]
				&& var->temp[0][i + j] == s2[j] && var->temp[1][i + j] == 'R')
			j++;
		if (s2[j] == '\0')
			break ;
		i++;
	}
	*a = i - 1;
	*b = j + i;
}

void	delete_str(t_mini *var, char **s1, char *s2)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	search_str(var, s2, &a, &b);
	while ((*s1)[b])
		(*s1)[a++] = (*s1)[b++];
	(*s1)[a] = '\0';
}

void	fill_temp(char **temp, char *str, int b)
{
	int	a;

	a = ft_strlen(str) - b ;
	*temp = malloc(a + 1);
	a = 0;
	while (str && str[b])
		(*temp)[a++] = str[b++];
	(*temp)[a] = 0;
}

void	insert_str(t_mini *var, char **str, char *s1, char *s2)
{
	char	*temp;
	int		a;
	int		b;

	a = 0;
	b = 0;
	search_str(var, s1, &a, &b);
	delete_str(var, str, s1);
	fill_temp(&temp, *str, a);
	b = 0;
	while (s2[b])
	{
		ft_realloc(str, 1);
		(*str)[a++] = s2[b++];
	}
	b = 0;
	while (temp[b])
	{
		ft_realloc(str, 1);
		(*str)[a++] = temp[b++];
	}
	free(temp);
}
