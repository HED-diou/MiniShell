/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profound_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 08:48:39 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/09 17:14:59 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_two_d(char *s1, char **str)
{
	int	a;

	a = 0;
	printf("%s\n", s1);
	while (str[a])
		printf("%s -- ", str[a++]);
	printf("\n_________________\n");
}

void	print_everthing(t_mini *mini)
{
	printf("cmd is >> \n%s\n", mini->cmd);
	print_two_d("options are >> ", mini->option);
	print_two_d("herdogs are >> ", mini->herdog);
	print_two_d("outputs are >> ", mini->rederct);
	printf("\n<-------------------------------\
			----------------------------------------->\n");
}

void	print_pipe(t_mini *mini)
{
	char	*str;

	while (mini)
	{
		str = NULL;
		if (mini->fd[0] != 0)
		{
			read_line(mini->fd[0], &str);
			printf("pipe >>> %s\n", str);
			free(str);
		}
		mini = mini->next;
	}
}
