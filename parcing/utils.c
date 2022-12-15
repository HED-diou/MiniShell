/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:51:37 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/09 14:39:06 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_realloc(char **str, int size)
{
	char	*p;
	int		a;
	int		len;

	a = 0;
	len = ft_strlen(*str) + 1;
	p = malloc(len + size + 1);
	if (!p)
		return ;
	while (*str && (*str)[a])
	{
		p[a] = (*str)[a];
		a++;
	}
	while (a < len + size)
		p[a++] = '\0';
	free(*str);
	*str = malloc(len + size + 1);
	a = -1;
	while (++a < len + size)
		(*str)[a] = p[a];
	free(p);
}

int	ft_strlen(const char *str)
{
	int	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a])
		a++;
	return (a);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\r' || c == '\t'
		|| c == '\v' || c == '\n' || c == '\f')
		return (0);
	return (1);
}

int	is_param(char c)
{
	if (c == '>' || c == '<'
		|| c == '|' || c == '(' || c == ')')
		return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	a;

	a = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[a] && s2[a] && s1[a] == s2[a])
		a++;
	return (s1[a] - s2[a]);
}
