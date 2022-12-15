/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 00:57:35 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/07 15:08:20 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	normal_add_env(char *title, char *option, int a, t_env *envp)
{
	char	*val;
	t_env	*new;

	a = 0;
	val = NULL;
	while (option[a])
	{
		ft_realloc(&val, 1);
		val[a] = option[a];
		a++;
	}
	if (exist_node(envp, title))
		replache_node(envp, title, option);
	else
	{
		new = ft_envnew(title, option, 1);
		ft_envadd_back(&envp, new);
	}
	free(val);
}

int	ft_export_variable_h(char *title, char *option, int a, t_env **envp)
{
	if (valid_title(title))
	{
		ft_put_err1("export: `", title, "': not a valid identifier", 2);
		free(title);
		g_data.exitcode = 1;
		return (-1);
	}
	else if (option[a] == '=')
	{
		normal_add_env(title, option + a + 1, a, *envp);
		free(title);
		return (-1);
	}
	else if (option[a] == '+' && option[a + 1] == '=')
	{
		a++;
		join_val(envp, title, option + a + 1, a);
		free(title);
		return (-1);
	}
	return (1);
}

int	ft_export_variable_helper(char *title, t_env **envp, char *option, int a)
{
	t_env	*new;

	new = NULL;
	if (ft_export_variable_h(title, option, a, envp) == -1)
		return (-1);
	else
	{
		if (!exist_node((*envp), title))
		{
			new = ft_envnew(title, "", 0);
			ft_envadd_back(envp, new);
		}
	}
	return (1);
}

void	ft_export_variable(t_env **envp, char *option, int a)
{
	char	*title;
	char	*val;

	title = NULL;
	val = NULL;
	if (ft_strlen(option) == 0 && option[0] != '=')
	{
		ft_put_err("", "export: `': not a valid identifier\n", 2);
		g_data.exitcode = 1;
		return ;
	}
	g_data.exitcode = 0;
	while (option[a])
	{
		ft_realloc(&title, 1);
		title[a] = option[a];
		a++;
		if ((option[a] == '+' && option[a + 1] == '=') || option[a] == '=')
			break ;
	}
	if (ft_export_variable_helper(title, envp, option, a) == -1)
		return ;
	free(title);
}

void	ft_export(t_env **envp, char **option)
{
	int	i;

	i = 0;
	if (option[0] == NULL)
	{
		set_index(envp);
		return ;
	}
	else
	{
		while (option[i])
		{
			ft_export_variable(envp, option[i], 0);
			i++;
		}
	}
}
