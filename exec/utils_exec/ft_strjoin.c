/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 01:35:36 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/05 02:23:40 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen((char *)s1);
		len2 = ft_strlen((char *)s2);
		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (!str)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		return (str);
	}
	return (NULL);
}

void	ft_put_err1(char *err, char *cmd, char *str, int fd)
{
	int	i;

	i = 0;
	while (err[i])
	{
		write(fd, &err[i], 1);
		i++;
	}
	i = 0;
	while (cmd[i])
	{
		write(fd, &cmd[i], 1);
		i++;
	}
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	ft_put_err(char *cmd, char *str, int fd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		write(fd, &cmd[i], 1);
		i++;
	}
	write(fd, " ", 1);
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd <= 100)
		close (fd++);
}

void	exec_builtins2(t_mini *mini, t_env **envp)
{
	ft_redirection(mini, 0);
	if (ft_strcmp(mini->cmd, "pwd") == 0)
		print_pwd(*envp);
	else if (ft_strcmp(mini->cmd, "env") == 0)
		ft_envp(*envp, mini);
	else if (ft_strcmp(mini->cmd, "cd") == 0)
	{
		if (!mini->option[0] || ft_strcmp(mini->option[0], "~") == 0)
			ft_cd(ft_home(*envp), *envp);
		else
			ft_cd(mini->option[0], *envp);
	}
	else if (ft_strcmp(mini->cmd, "exit") == 0)
		ft_exit(mini);
	else if (ft_strcmp(mini->cmd, "echo") == 0)
		ft_echo(mini->option);
	else if (ft_strcmp(mini->cmd, "unset") == 0)
	{
		if (mini->option[0])
			ft_unset(envp, mini->option);
	}
	else if (ft_strcmp(mini->cmd, "export") == 0)
		ft_export(envp, mini->option);
}
