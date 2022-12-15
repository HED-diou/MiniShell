/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:24:17 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/07 14:59:16 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_envp(t_env *envp, t_mini *mini)
{
	if (mini->option[0] != NULL)
	{
		ft_put_err("", "env: No such file or directory\n", 2);
		g_data.exitcode = 127;
		return ;
	}
	else
	{
		g_data.exitcode = 0;
		while (envp)
		{
			if (envp->sw == 1)
			{
				printf("%s=%s\n", envp->title, envp->val);
			}
			envp = envp->next;
		}
	}
}
