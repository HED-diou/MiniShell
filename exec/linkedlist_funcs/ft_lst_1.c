/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:15:09 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/06 01:20:48 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstdelone(t_env *lst, void (*del)(void*))
{
	if (lst && del)
	{
		(del)(lst->title);
		(del)(lst->val);
		free(lst);
	}
	lst = NULL;
}

t_env	*ft_envnew(char *title, char *content, int i)
{
	t_env	*c;

	c = (t_env *)malloc(sizeof(t_env));
	if (!c)
		return (NULL);
	c->title = ft_strdup(title);
	c->val = ft_strdup(content);
	c->index = 0;
	c->sw = i;
	c->next = NULL;
	return (c);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_envadd_back(t_env **alst, t_env *new)
{
	t_env	*l;

	if (*alst)
	{
		l = ft_lstlast(*alst);
		l -> next = new;
	}
	else
	{
		*alst = new;
	}
}

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
