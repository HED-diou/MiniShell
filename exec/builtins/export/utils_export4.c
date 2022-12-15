/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:08:07 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/06 01:21:06 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	join_val(t_env **envp, char *title, char *option, int a)
{
	char	*val;
	char	*tmp;
	t_env	*temp;

	a = 0;
	temp = *envp;
	tmp = NULL;
	val = NULL;
	while (option[a])
	{
		ft_realloc(&val, 1);
		val[a] = option[a];
		a++;
	}
	join_val_help(envp, title, val, tmp);
	*envp = temp;
	free(val);
}

int	ft_lstsize1(t_mini *lst)
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
