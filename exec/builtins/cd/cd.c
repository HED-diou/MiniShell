/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:20:50 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/07 15:16:07 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*ft_home(t_env *envp)
{	
	char	*val;

	val = NULL;
	while (envp)
	{
		if (strcmp(envp->title, "HOME") == 0)
			return (envp->val);
		envp = (envp->next);
	}
	return (0);
}

char	*change_pwd_on_cd(t_env *envp, char *pwd, char	*cwd)
{
	while (envp)
	{
		if (strcmp(envp->title, "PWD") == 0)
		{
			pwd = ft_strdup(envp->val);
			free(envp->val);
			envp->val = NULL;
			envp->val = ft_strdup(getcwd(cwd, 256));
			return (pwd);
		}
		envp = envp->next;
	}
	return (0);
}

void	change_oldpwd_on_cd(t_env *envp, char *pwd)
{
	while (envp)
	{
		if (strcmp(envp->title, "OLDPWD") == 0)
		{
			if (envp->val)
			{
				free(envp->val);
				envp->val = NULL;
				envp->val = ft_strdup(pwd);
			}
			break ;
		}
		envp = envp->next;
	}
}

void	ft_cd(char *cd, t_env *envp)
{
	t_env	*tmp;
	char	*pwd;
	char	*cwd;

	tmp = envp;
	pwd = NULL;
	if (ft_strcmp(cd, ".") == 0)
		return ;
	if (chdir(cd) == -1)
	{
		g_data.exitcode = 1;
		perror("error");
		return ;
	}
	cwd = malloc(256);
	g_data.exitcode = 0;
	pwd = change_pwd_on_cd(envp, pwd, cwd);
	envp = tmp;
	change_oldpwd_on_cd(envp, pwd);
	free(pwd);
	free(cwd);
}
