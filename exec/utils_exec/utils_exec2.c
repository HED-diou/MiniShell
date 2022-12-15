/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:46:25 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/09 18:13:41 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_path(char *cmd, t_env *envp)
{
	int		i;
	char	*res;
	char	**path;

	path = ft_split(ft_pathindex(envp), ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], "/");
	i = -1;
	while (path[++i])
	{
		res = ft_strjoin(path[i], cmd);
		if (access(res, F_OK) == 0 || access(res, X_OK) == 0)
		{
			free_strs(path);
			return (res);
		}
		free(res);
	}
	free_strs(path);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (get_env(envp, "PATH") == NULL)
		ft_put_err(cmd, ":  No such file or directory\n", 2);
	return (NULL);
}

char	**cmd_option(t_mini *mini)
{
	char	**temp;
	int		a;
	int		b;

	b = 0;
	if (!mini->cmd && !mini->option)
		return (NULL);
	a = 0;
	while (mini->option[a])
		a++;
	temp = malloc(sizeof(char *) * (a + 2));
	temp[0] = ft_strdup(mini->cmd);
	a = 1;
	while (mini->option[b])
	{
		temp[a] = ft_strdup(mini->option[b]);
		a++;
		b++;
	}
	temp[a] = NULL;
	return (temp);
}

void	error_exeption(char *error)
{
	perror(error);
	g_data.exitcode = 1;
	if (g_data.a == 0)
		exit(g_data.exitcode);
}

void	ft_pipes(t_mini *mini, int *fd, int i, int n)
{
	if (n != 1)
	{
		if (i == 0)
		{
			dup2(fd[i + 1], 1);
		}
		else if (i != 0 && mini->next)
		{
			dup2(fd[i - 2], 0);
			dup2(fd[i + 1], 1);
		}
		else if (mini->next == NULL)
		{
			dup2(fd[i - 2], 0);
		}
	}
	ft_redirection(mini, i);
}
