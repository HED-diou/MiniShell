/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:24:51 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/09 19:05:27 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	duplicat_temp(t_mini *mini, int b)
{
	int	a;

	a = 0;
	mini->temp[1] = malloc(b + 1);
	mini->temp[2] = malloc(b + 1);
	while (a < b)
	{
		mini->temp[1][a] = '0';
		mini->temp[2][a] = '0';
		a++;
	}
	mini->temp[1][a] = '\0';
	mini->temp[2][a] = '\0';
}

void	ft_essentials(t_mini *mini, t_env *env, char **str)
{
	flag_quotes(mini, 0, 0);
	set_space(mini);
	valid_opertors(mini);
	valid_var(mini);
	delete_invalid_vars(mini, env, str);
	get_simple_herdog(mini);
	get_simple_catfile(mini);
	get_simple_cmd(mini);
	get_simple_option(mini);
}

void	global_copy(t_mini **mini, t_mini **lst)
{
	(*mini)->operater = (*lst)->operater;
	(*mini)->option = (*lst)->option;
	(*lst)->option = NULL;
	(*mini)->herdog = (*lst)->herdog;
	(*lst)->herdog = NULL;
	(*mini)->rederct = (*lst)->rederct;
	(*lst)->rederct = NULL;
	(*mini)->cmd = (*lst)->cmd;
	(*lst)->cmd = NULL;
	(*mini)->next = NULL;
}

int	fill_comp(t_mini *mini, t_env *env, char **str, int b)
{
	mini->a++;
	duplicat_temp(mini, b);
	ft_essentials(mini, env, str);
	free_temps(mini);
	return (0);
}

void	fill_list(char **str, t_mini **mini, t_env *env)
{
	t_mini	*lst;
	int		a;
	int		b;

	a = 0;
	b = 0;
	lst = malloc(sizeof(t_mini));
	while ((*str)[a])
	{
		if (b == 0)
		{
			lst->temp = malloc(sizeof(char *) * 3);
			lst->temp[0] = NULL;
		}
		ft_realloc(&(lst->temp[0]), 1);
		lst->temp[0][b++] = (*str)[a++];
		if (a == valid_pipe(*str, a))
		{
			b = fill_comp(lst, env, str, b);
			lst_add_back(mini, lst);
		}
	}
	free(lst);
}
