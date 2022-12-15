/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:37:37 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/07 15:10:03 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	fun(void *head)
{
	free(head);
}

int	valid_title1(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[0]) && !ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_' )
			return (0);
		i++;
	}
	return (1);
}

void	unset_node(t_env *tmp, t_env *prev, char *line)
{
	while (tmp)
	{
		if (strcmp(tmp->title, line) == 0)
		{
			if (tmp->next)
			{
				prev->next = tmp->next;
				ft_lstdelone(tmp, fun);
				return ;
			}
			else
			{
				prev->next = NULL;
				ft_lstdelone(tmp, fun);
				return ;
			}
		}
		prev = prev->next;
		tmp = tmp->next;
	}
}

void	unset_func(t_env **envp, t_env *tmp, t_env *prev, char **line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!valid_title1(line[i]) || ft_strcmp(line[i], "") == 0)
		{
			ft_put_err1("unset: `", line[i], "': not a valid identifier", 2);
			g_data.exitcode = 1;
		}
		else
		{
			g_data.exitcode = 0;
			if (strcmp((*envp)->title, line[i]) == 0)
			{
				*envp = (*envp)->next;
				ft_lstdelone(prev, fun);
			}
			unset_node(tmp, prev, line[i]);
		}
		i++;
	}
}

void	ft_unset(t_env **envp, char **line)
{	
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 0;
	tmp = (*envp)->next;
	prev = *envp;
	unset_func(envp, tmp, prev, line);
}
