/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:05:08 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/06 00:12:33 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	valid_title(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (i == 0)
		{
			if (ft_isdigit(var[i]) || (!ft_isalpha(var[i]) && var[i] != '_'))
				return (1);
		}
		else if (!ft_isalpha(var[i]) && var[i] != '_' && !ft_isdigit(var[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strcher(char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			return (&str[i]);
		i++;
	}
	if (ch == '\0')
		return (&str[i]);
	return (0);
}

// int	char_chr(char *line, char c)
// {
// 	int	i;

// 	i = ft_strlen(line) - 1;
// 	if (line[i] == '+')
// 		return (1);
// 	return (0);
// }

void	join_val_helper_plus(t_env **envp, char *title, char *tmp, char *val)
{
	while (*envp)
	{
		if (ft_strcmp((*envp)->title, title) == 0)
		{
			if (val == NULL)
				break ;
			tmp = (*envp)->val;
			(*envp)->val = ft_strjoin(tmp, val);
			free(tmp);
			tmp = NULL;
			break ;
		}
		(*envp) = (*envp)->next;
	}
}

void	join_val_help(t_env **envp, char *title, char *val, char *tmp)
{
	t_env	*new;

	new = NULL;
	if (exist_node(*envp, title))
	{
		join_val_helper_plus(envp, title, tmp, val);
	}
	else
	{
		if (val == NULL)
			val = ft_strdup("");
		new = ft_envnew(title, val, 1);
		ft_envadd_back(envp, new);
	}
}
