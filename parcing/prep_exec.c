/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:48:35 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/11 12:15:59 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **env, t_env **envp)
{
	int		i;
	char	**tmp;
	t_env	*t;

	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		t = ft_envnew(tmp[0], tmp[1], 1);
		ft_envadd_back(envp, t);
		i++;
		free_strs(tmp);
	}
}

char	**convert_env(t_env *envp)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc((sizeof(char *)) * (ft_lstsize(envp) + 1));
	while (envp)
	{
		res[i] = NULL;
		strcpy_adres(&res[i], envp->title);
		strcat_adres(&res[i], "=");
		strcat_adres(&res[i], envp->val);
		i++;
		envp = envp->next;
	}
	res[i] = NULL;
	return (res);
}

void	prep_exec(t_mini *mini, t_env **envp)
{
	char	**env2d;

	env2d = convert_env(*envp);
	if (g_data.sig == 0)
	{
		if (is_builtins(mini->cmd) == 1 && mini->next == NULL)
			exec_builtins(mini, envp);
		else
			execution(mini, envp, env2d);
	}
	if (g_data.flag[0] != -1)
		close(g_data.flag[0]);
	free_strs(env2d);
}
