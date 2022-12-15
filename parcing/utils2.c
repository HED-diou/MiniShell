/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:10:10 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/10 20:12:15 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fprint(char *str)
{
	write(1, str, ft_strlen(str));
}

int	read_line(int fd, char **str)
{
	int	a;
	int	s;

	a = 1;
	s = ft_strlen(*str);
	if (fd <= 0)
		return (0);
	while (a > 0)
	{
		ft_realloc(str, 1);
		a = read(fd, (*str + s), 1);
		if ((*str)[s] == 0)
			break ;
		s++;
	}
	return (a);
}

void	lst_add_back(t_mini **mini, t_mini *lst)
{
	t_mini	*temp2;
	t_mini	*temp;

	temp = *mini;
	temp2 = NULL;
	if (!(*mini))
	{
		*mini = malloc(sizeof(t_mini));
		global_copy(mini, &lst);
		(*mini)->next = NULL;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp2 = malloc(sizeof(t_mini));
		global_copy(&temp2, &lst);
		temp->next = temp2;
		temp2->next = NULL;
	}
}

char	*ft_strdup(char *t1)
{
	int		n;
	char	*t2;
	int		i;

	n = 0;
	if (!t1)
		return (NULL);
	while (t1[n])
		n++;
	t2 = (char *)malloc((n + 1) * sizeof(char));
	if (t2 == NULL)
		return (0);
	i = 0;
	while (t1[i])
	{
		t2[i] = t1[i];
		i++;
	}
	t2[i] = '\0';
	return (t2);
}
