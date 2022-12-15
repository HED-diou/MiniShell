/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:30:12 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/11 13:14:30 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_exit(int sig)
{
	exit(sig);
}

int	*init_fd(int n)
{
	int	*fd;
	int	i;

	i = 0;
	fd = malloc(((n - 1) * 2) * sizeof(int));
	while (i < (n - 1) * 2 && n != 1)
	{
		pipe(&fd[i]);
		i += 2;
	}
	return (fd);
}

void	exec_builtins_cmd(t_mini *mini, t_env **envp)
{
	if (is_builtins(mini->cmd))
		exec_builtins(mini, envp);
}

void	exec_child(t_mini *mini, int *fd, t_env **envp, char **temp)
{
	int	i;
	int	fd2;
	int	n;

	n = ft_lstsize1(mini);
	i = 0;
	while (mini)
	{
		if (fork() == 0)
		{
			signal(SIGQUIT, &child_exit);
			fd2 = mini->fd[0];
			ft_pipes(mini, fd, i, n);
			exec_builtins_cmd(mini, envp);
			if (!is_builtins(mini->cmd))
			{
				close_fd(n, fd);
				exec_it(mini, fd2, envp, temp);
			}
			close(mini->fd[0]);
			exit(g_data.exitcode);
		}
		mini = mini->next;
		i += 2;
	}
}

void	execution(t_mini *mini, t_env **envp, char **temp)
{
	int	exitstatus;
	int	*fd;
	int	n;

	n = ft_lstsize1(mini);
	fd = init_fd(n);
	g_data.a = 0;
	pipe(g_data.flag);
	write(g_data.flag[1], "1", 1);
	exec_child(mini, fd, envp, temp);
	close_fd(n, fd);
	free(fd);
	n = 0;
	while (wait(&exitstatus) != -1)
		n++;
	if (WIFEXITED(exitstatus))
		g_data.exitcode = WEXITSTATUS(exitstatus);
	n = 4;
	close_fds();
}
