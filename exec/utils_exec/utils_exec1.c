/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:31:41 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/09 22:09:50 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_managment(char *cmd, char *func)
{
	if (ft_strcmp(func, "execve") == 0)
	{
		if (ft_strnstr(cmd, "/", ft_strlen(cmd)) != 0)
		{
			write(2, cmd, ft_strlen(cmd));
			write(2, ": No such file or directory\n", 28);
			exit(127);
		}
		else
		{
			write(2, cmd, ft_strlen(cmd));
			write(2, ": command not found\n", 21);
			exit(127);
		}
	}
}

int	is_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else
		return (0);
}

void	exec_builtins(t_mini *mini, t_env **envp)
{
	int	out;
	int	in;

	in = dup(0);
	out = dup(1);
	exec_builtins2(mini, envp);
	dup2(out, 1);
	dup2(in, 0);
}

int	is_new_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_pathindex(t_env *envp)
{
	while (envp)
	{
		if (ft_strnstr(envp->title, "PATH", 5) != NULL)
			return (envp->val);
		envp = envp->next;
	}
	return (0);
}
