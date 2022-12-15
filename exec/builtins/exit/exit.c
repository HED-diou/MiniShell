/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:48:04 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/07 16:07:40 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

long long	ft_atoi(char *str)
{
	int			a;
	int			sign;
	long long	num;

	a = 0;
	sign = 1;
	num = 0;
	while (is_space(str[a]) == 0)
		a++;
	while (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			sign = -sign;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		num = (num * 10) + str[a] - '0';
		a++;
	}
	return (num * sign);
}

void	exit_args_check(t_mini *mini, int c, int i)
{
	if (i == 0)
	{
		if (mini->option[1] != NULL)
		{
			g_data.exitcode = 255;
			write(2, "exit: too many arguments\n", 25);
			exit(g_data.exitcode);
		}
	}
	while (is_space(mini->option[i][c]) == 0)
		c++;
	if (mini->option[i][c] == '-' || mini->option[i][c] == '+')
		c++;
	while (mini->option[i][c])
	{
		if (!ft_isdigit(mini->option[i][c]))
		{
			ft_put_err1("exit: ", mini->option[i],
				" numeric argument required", 2);
			g_data.exitcode = 255;
			exit(g_data.exitcode);
		}
		c++;
	}
}

int	exitcode_traitement(int exit)
{
	g_data.exitcode = exit;
	if (g_data.exitcode >= 0)
		g_data.exitcode = g_data.exitcode % 255;
	else
	{
		g_data.exitcode = g_data.exitcode * -1;
		g_data.exitcode = g_data.exitcode % 256;
		g_data.exitcode = 256 - g_data.exitcode;
	}
	return (g_data.exitcode);
}

void	ft_exit_args(t_mini *mini)
{
	int	a;

	a = 0;
	if (mini->option[1] == NULL)
	{
		g_data.exitcode = 0;
		exit(g_data.exitcode = 0);
	}
	else
	{
		exit_args_check(mini, 0, 1);
		g_data.exitcode = ft_atoi(mini->option[1]);
		exit(exitcode_traitement(g_data.exitcode));
	}
}

void	ft_exit(t_mini *mini)
{
	long long	b;
	int			c;

	b = 0;
	c = 0;
	if (mini->option[0] == NULL)
		exit(g_data.exitcode);
	while (mini->option[c])
		c++;
	if (c > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		g_data.exitcode = 1;
	}
	else
	{
		if (strcmp(mini->option[0], "--") == 0)
			ft_exit_args(mini);
		exit_args_check(mini, 0, 0);
		g_data.exitcode = ft_atoi(mini->option[0]);
		exit(exitcode_traitement(g_data.exitcode));
	}
}
