/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:50:16 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/11 12:16:16 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_errors(char *str, t_env *env)
{
	int		a;
	t_mini	mini;

	a = 1;
	fill_par(&mini, str);
	flag_quotes(&mini, 0, 0);
	if (single_quote_error(&mini) == 1)
	{
		free_temps(&mini);
		return (0);
	}
	set_space(&mini);
	valid_opertors(&mini);
	a = check_errors(&mini);
	if (a == 0)
		empty_herdoc(&mini, env);
	free_temps(&mini);
	return (a);
}

void	null_line(char *line)
{
	if (line == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}
