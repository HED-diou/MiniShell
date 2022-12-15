/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:47:35 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/11 13:24:47 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_c(int a)
{
	int		b;
	char	c;

	c = 0;
	b = 0;
	(void)a;
	close(g_data.flag[1]);
	check_sig(g_data.flag[0], &c);
	if (c == '1')
	{
		g_data.exitcode = 130;
		close(g_data.flag[0]);
		b = 1;
	}
	if (b == 0)
	{
		g_data.exitcode = 1;
		write(1, "\n", 1);
		rl_on_new_line();
	}
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ixit(int key)
{
	(void)key;
	rl_replace_line("", 0);
	rl_redisplay();
	write(g_data.flag[1], "1", 1);
	exit(0);
}

void	herdoc_sig(int sig)
{
	write(g_data.flag[1], "1", 1);
	rl_replace_line("", 0);
	exit(sig);
}

void	set_list(t_mini **mini, t_env **envp, char **line)
{
	if (ft_errors(*line, *envp) == 0 || ft_strlen(*line) == 0)
	{
		record_history(*line);
		return ;
	}
	g_data.sig = 0;
	g_data.a = 1;
	g_data.flag[0] = -1;
	open_pipe(line, *envp);
	record_history(*line);
	fill_list(line, mini, *envp);
	excute_hedoc_2(*mini, *envp);
	expand_all_vars(mini, *envp);
	prep_exec(*mini, envp);
	free_list(mini);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_mini	*mini;
	t_env	*envp;

	(void)ac;
	(void)av;
	mini = NULL;
	envp = NULL;
	g_data.flag[1] = -1;
	charge_history();
	ft_env(env, &envp);
	signal(SIGINT, &ctl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_data.sig = 0;
		line = readline("\033[0;32m╭─minishell@hed-najib ~/ \n╰─[>>$ ");
		null_line(line);
		set_list(&mini, &envp, &line);
		free(line);
		line = NULL;
	}
}
