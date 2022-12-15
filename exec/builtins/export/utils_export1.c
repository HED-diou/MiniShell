/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:00:11 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/06 00:12:26 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_isalpha(int chr)
{
	if ((chr >= 65 && chr <= 90) || (chr >= 97 && chr <= 122))
	{
		return (1);
	}
	return (0);
}

int	ft_isdigit(int arg)
{
	if (arg >= 48 && arg <= 57)
	{
		return (1);
	}
	return (0);
}

void	print_export_line(t_env *envp)
{
	if (envp->sw == 1)
		printf("declare -x %s=\"%s\"\n", envp->title, envp->val);
	else
		printf("declare -x %s\n", envp->title);
}

void	ft_print_export(t_env **head)
{
	t_env	*tmp;
	int		i;

	tmp = *head;
	i = 1;
	while (tmp)
	{
		if (tmp->index == i)
		{
			print_export_line(tmp);
			tmp = *head;
			i++;
		}
		tmp = tmp->next;
	}
}

t_env	*ft_getnode(t_env *node)
{
	while (node)
	{
		if (node->index == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}
