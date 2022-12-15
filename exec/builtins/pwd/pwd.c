/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:34:04 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/07 14:25:15 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_pwd(t_env *envp)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	g_data.exitcode = 0;
	while (envp)
	{
		if (strcmp(envp->title, "PWD") == 0)
		{
			if (ft_strcmp(cwd, envp->val) == 0)
				printf("%s\n", cwd);
			else
				printf("%s\n", envp->val);
		}
		envp = envp->next;
	}
}
