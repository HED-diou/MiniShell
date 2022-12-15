/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quate_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:24:38 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/10 17:33:43 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_quote_error(t_mini *mini)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 0;
	c = 0;
	while (mini->temp[1][a])
	{
		if (mini->temp[1][a] == '3')
			c++;
		if (mini->temp[1][a] == '4')
			b++;
		a++;
	}
	if (c > 0 || b > 0)
		return (1);
	return (0);
}

void	shift_str(t_mini *mini, int a, int c)
{
	int	b;

	b = a + c;
	while (mini->temp[0][b])
	{
		mini->temp[0][a] = mini->temp[0][b];
		mini->temp[1][a] = mini->temp[1][b];
		mini->temp[2][a] = mini->temp[2][b];
		a++;
		b++;
	}
	mini->temp[0][a] = '\0';
	mini->temp[1][a] = '\0';
	mini->temp[2][a] = '\0';
}

void	strcpy_adres(char **str, char *s)
{
	int	a;
	int	b;

	a = 0;
	if (!s)
		return ;
	b = ft_strlen(s);
	*str = malloc(b + 2);
	while (s[a])
	{
		(*str)[a] = s[a];
		a++;
	}
	(*str)[a] = 0;
}

void	strcat_adres(char **str, char *s)
{
	int	a;
	int	b;

	a = 0;
	if (!s)
		return ;
	b = ft_strlen(*str);
	while (s[a])
	{
		ft_realloc(str, 2);
		(*str)[b] = s[a];
		a++;
		b++;
	}
	(*str)[b] = 0;
}

char	*remove_quote(char *str)
{
	char	*temp;
	t_mini	lst;

	temp = ft_strdup(str);
	set_struct(&lst, temp);
	delete_quote(&lst, &temp);
	free_temps(&lst);
	return (temp);
}
