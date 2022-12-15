/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:57:38 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/11 12:56:03 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_env *env, char *str)
{
	char	*temp;

	temp = NULL;
	while (env)
	{
		if (ft_strcmp(str, env->title) == 0 && env->sw == 1)
		{
			strcpy_adres(&temp, env->val);
			break ;
		}
		env = env->next;
	}
	return (temp);
}

int	delete_vars(t_mini *mini, t_env *env, char **str, char *temp)
{
	char	*p;

	if (ft_strcmp(temp, "?") == 0)
		return (1);
	p = get_env(env, temp);
	if (p == NULL)
	{
		delete_str(mini, str, temp);
		return (0);
	}
	free(p);
	return (1);
}

int	delete_util(t_mini *mini, t_env *env, char **str, int a)
{
	int		b;
	char	*temp;

	b = 0;
	temp = NULL;
	while (mini->temp[1][a] && mini->temp[1][a] == '0' &&
			allowed_chars(mini->temp[0][a]) == 1)
	{
		ft_realloc(&temp, 1);
		mini->temp[1][a] = 'R';
		temp[b++] = (*str)[a++];
	}
	if (delete_vars(mini, env, str, temp) == 0)
		a = 0;
	free(temp);
	return (a);
}

void	delete_invalid_vars(t_mini *mini, t_env *env, char **str)
{
	int	a;

	a = 0;
	while (mini->temp[0][a])
	{
		if (mini->temp[1][a] == 'V' && allowed_chars(mini->temp[0][a + 1]) == 1)
		{
			mini->temp[1][a] = 'R';
			a++;
			if (delete_util(mini, env, str, a) == 0)
				a = 0;
			if (ft_strlen(*str) <= 1)
				break ;
			free_temps(mini);
			set_struct(mini, *str);
		}
		else
			a++;
	}
}
