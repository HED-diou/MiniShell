/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:24:50 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/06 13:06:53 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	pas_args(char **option, int *i, int *j, int *n)
{
	*n = 0;
	while (option && option[*i])
	{
		*j = 0;
		if (option[*i][*j] == '-' && option[*i][*j + 1] == '\0')
			break ;
		if (option[*i][(*j)++] == '-')
		{
			while (option[*i][*j] == 'n')
				(*j)++;
			if (option[*i][*j] != 'n' && option[*i][*j] != '\0')
				break ;
			else
				*n = 1;
		}
		else
			break ;
		(*i)++;
	}
}

void	ft_echo(char **option)
{
	int	n;
	int	i;
	int	j;

	i = 0;
	n = 0;
	j = 0;
	if (!option)
	{
		printf("\n");
		return ;
	}
	pas_args(option, &i, &j, &n);
	while (option[i])
	{
		printf("%s", option[i]);
		i++;
		if (option[i])
			printf(" ");
	}
	if (n != 1)
		printf("\n");
	g_data.exitcode = 0;
}
