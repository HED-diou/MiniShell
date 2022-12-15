/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:48:13 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/10 20:15:23 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_writfile(char **out)
{
	int	fd_in;

	fd_in = 0;
	if (ft_strcmp(out[1], "c") == 0)
		fd_in = open(out[0], O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (ft_strcmp(out[1], "o") == 0)
		fd_in = open(out[0], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_in == -1)
		error_exeption(out[0]);
	dup2(fd_in, 1);
	close(fd_in);
}

void	ft_readfile(char *out)
{
	int	fd_out;

	fd_out = open(out, O_RDWR, 0777);
	if (fd_out == -1)
		error_exeption(out);
	dup2(fd_out, 0);
	close(fd_out);
}

void	ft_redirection(t_mini *mini, int i)
{
	char	**out;

	if (mini->rederct[0])
	{
		i = 0;
		while (mini->rederct[i])
		{
			out = ft_split(mini->rederct[i], ' ');
			if (ft_strcmp(out[1], "x") == 0)
				ft_readfile(out[0]);
			else
				ft_writfile(out);
			i++;
			free_strs(out);
		}
	}
}

void	close_fd(int n, int *fd)
{
	int	j;

	j = 0;
	while (j < (n - 1) * 2)
	{
		close(fd[j]);
		j++;
	}
}

void	exec_it(t_mini *mini, int fd2, t_env **envp, char **temp)
{
	if (mini->cmd == NULL)
		exit(0);
	if (mini->herdog[0] && fd2 != 0)
		dup2(fd2, 0);
	if (execve(get_path(mini->cmd, *envp), cmd_option(mini), temp) == -1)
		error_managment(mini->cmd, "execve");
}
