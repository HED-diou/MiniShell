/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:02:03 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/11 12:11:35 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_expand(t_mini *mini, t_env *env, char **line, int u)
{
	t_mini	lst;
	int		a;

	a = 0;
	if (ft_strlen(*line) <= 0)
		return ;
	set_struct(&lst, *line);
	while (mini->herdog[u][a] && mini->herdog[u][a] != '"' &&
			mini->herdog[u][a] != 39)
		a++;
	if (a == ft_strlen(mini->herdog[u]))
		expand_var(&lst, env, line);
	free_temps(&lst);
}

int	check_lim(t_mini *mini, char *line, char **buff, int u)
{
	char	*temp;

	temp = remove_quote(mini->herdog[u]);
	if (ft_strcmp(line, temp) == 0)
	{
		if (mini->herdog[u + 1] == NULL)
			return (-1);
		u++;
	}
	if (!mini->herdog[u + 1] && ft_strlen(line) > 0 && \
			ft_strcmp(line, temp))
	{
		strcat_adres(buff, line);
		strcat_adres(buff, "\n");
	}
	free(temp);
	return (u);
}

void	fill_herdoc(t_mini *mini, t_env *env)
{
	char	*line;
	char	*buff;
	int		u;

	u = 0;
	buff = NULL;
	while (1)
	{
		line = readline("herdoc $> ");
		if (line == NULL && mini->herdog[++u] == NULL)
			break ;
		check_expand(mini, env, &line, u);
		u = check_lim(mini, line, &buff, u);
		if (u == -1)
			break ;
		free(line);
	}
	write(mini->fd[1], buff, ft_strlen(buff));
	exit(0);
}

int	save_sig(t_mini *mini)
{
	int		a;
	char	c;

	c = 0;
	a = 0;
	close(mini->fd[1]);
	check_sig(g_data.flag[0], &c);
	if (c == '1')
	{
		g_data.sig = 1;
		return (0);
	}
	return (1);
}

void	excute_hedoc_2(t_mini *mini, t_env *env)
{
	while (mini)
	{
		if (mini->herdog[0] == NULL)
			mini->fd[0] = 0;
		if (mini->herdog[0] != NULL)
		{
			pipe(g_data.flag);
			pipe(mini->fd);
			if (fork() == 0)
			{
				signal(SIGINT, &herdoc_sig);
				signal(SIGQUIT, SIG_IGN);
				fill_herdoc(mini, env);
			}
			close(g_data.flag[1]);
			wait(NULL);
			if (save_sig(mini) == 0)
				break ;
		}
		mini = mini->next;
	}
}
