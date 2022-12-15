/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:58:48 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/08 09:54:06 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	allowed_chars(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_' || c == '?')
		return (1);
	return (0);
}

void	check_var(t_mini *var, t_env *env, char **str, char *temp)
{
	char	*p;
	int		a;

	a = 0;
	if (ft_strcmp(temp, "?") == 0)
	{
		p = ft_itoa(g_data.exitcode);
		insert_str(var, str, temp, p);
		free(p);
		return ;
	}
	p = get_env(env, temp);
	if (p == NULL)
		delete_str(var, str, temp);
	else
		insert_str(var, str, temp, p);
	free(p);
}

void	expand_util(t_mini *var, t_env *env, char **str, int a)
{
	int		b;
	char	*temp;

	b = 0;
	temp = NULL;
	while (var->temp[1][a] && var->temp[1][a] == '0' &&
			allowed_chars(var->temp[0][a]) == 1)
	{
		ft_realloc(&temp, 1);
		var->temp[1][a] = 'R';
		temp[b++] = (*str)[a++];
	}
	check_var(var, env, str, temp);
	free(temp);
}

void	expand_var(t_mini *var, t_env *env, char **str)
{
	int	a;

	a = 0;
	while (var->temp[0][a])
	{
		if (var->temp[1][a] == 'V' && allowed_chars(var->temp[0][a + 1]) == 1)
		{
			var->temp[1][a] = 'R';
			a++;
			expand_util(var, env, str, a);
			free_temps(var);
			set_struct(var, *str);
			a = 0;
		}
		else
			a++;
	}
}

void	simple_all(char **str, t_env *env)
{
	t_mini	var;

	if (*str == NULL)
		return ;
	set_struct(&var, *str);
	expand_var(&var, env, str);
	delete_quote(&var, str);
	free_temps(&var);
}
