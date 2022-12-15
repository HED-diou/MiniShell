/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:59:17 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/11 15:13:30 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strs(char **str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		free(str[a]);
		str[a] = NULL;
		a++;
	}
	free(str);
}

void	free_list(t_mini **mini)
{
	t_mini	*temp;

	while (*mini)
	{
		temp = *mini;
		free_strs((*mini)->herdog);
		free_strs((*mini)->rederct);
		free_strs((*mini)->option);
		free((*mini)->cmd);
		*mini = (*mini)->next;
		free(temp);
	}
	*mini = NULL;
}

void	free_temps(t_mini *mini)
{
	free(mini->temp[0]);
	mini->temp[0] = NULL;
	free(mini->temp[1]);
	mini->temp[1] = NULL;
	free(mini->temp[2]);
	mini->temp[2] = NULL;
	free(mini->temp);
	mini->temp = NULL;
}

void	free_all(t_mini *mini)
{
	if (mini->a == 0)
		return ;
	free_strs(mini->herdog);
	free_strs(mini->option);
	free(mini->cmd);
}
