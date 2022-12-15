/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:03:46 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/07 15:08:45 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	set_zero(t_env **node)
{
	t_env	*tmp;

	tmp = *node;
	while ((*node))
	{
		(*node)->index = 0;
		(*node) = (*node)->next;
	}
	*node = tmp;
}

void	set_index_helper(t_env **st, t_env *temp1, t_env *temp2)
{
	int	s;
	int	a;

	a = 1;
	s = ft_lstsize(*st) + 1;
	while (a <= s)
	{
		(*st) = ft_getnode(temp2);
		if (*st == NULL)
			break ;
		temp1 = *st;
		while (*st)
		{
			if (ft_strcmp(temp1->title, (*st)->title) > 0 && (*st)->index == 0)
				temp1 = *st;
			(*st) = (*st)->next;
		}
		temp1->index = a;
		if (temp1->sw == 1)
			print_export_line(temp1);
		*st = temp1;
		a++;
	}
}

void	set_index(t_env **st)
{
	t_env	*temp1;
	t_env	*temp2;
	int		a;
	int		s;

	temp1 = *st;
	temp2 = *st;
	s = ft_lstsize(*st) + 1;
	a = 1;
	set_index_helper(st, temp1, temp2);
	*st = temp2;
	temp1 = *st;
	while (temp1)
	{
		if (temp1->sw == 0)
			print_export_line(temp1);
		temp1 = temp1->next;
	}
	*st = temp2;
	set_zero(st);
}

int	exist_node(t_env *envp, char *title)
{
	while (envp)
	{
		if (!ft_strcmp(envp->title, title))
			return (1);
		envp = envp->next;
	}
	return (0);
}

void	replache_node(t_env *envp, char *title, char *val)
{
	t_env	*tmp;

	tmp = envp;
	while (envp)
	{
		if (ft_strcmp(envp->title, title) == 0)
		{
			free(envp->val);
			(envp)->val = NULL;
			(envp)->val = ft_strdup(val);
			envp->sw = 1;
			break ;
		}
		envp = (envp)->next;
	}
	(envp) = tmp;
}
