/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:04:07 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/10 15:04:40 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count(char *str)
{
	int	b;
	int	a;

	b = 0;
	a = ft_strlen(str);
	while (str[b] && is_space(str[b]) == 0)
		b++;
	if (a == b)
		return (0);
	return (1);
}

int	check_end(char *temp)
{
	int	a;

	if (temp == NULL)
	{
		fprint("syntax error: unexpected end of file\n");
		exit(0);
	}
	a = ft_strlen(temp) - 1;
	if (a > 0 && temp[a] != '|' && ft_count(temp))
	{
		free(temp);
		return (-1);
	}
	return (1);
}

void	get_pipe(int *fd, t_env *env)
{
	int		a;
	char	*temp;
	char	*buff;

	buff = NULL;
	signal(SIGINT, &ixit);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		temp = readline("pipe >  ");
		a = ft_strlen(temp);
		if (a > 0 && ft_count(temp))
			strcat_adres(&buff, temp);
		if (a > 0 && ft_errors(temp, env) == 0)
			exit(0);
		if (check_end(temp) == -1)
			break ;
		free(temp);
		temp = NULL;
	}
	write(fd[1], buff, ft_strlen(buff));
	exit(0);
}

void	open_pipe(char **str, t_env *env)
{
	int		a;
	t_mini	lst;
	int		fd[2];

	pipe(fd);
	pipe(g_data.flag);
	set_struct(&lst, *str);
	a = ft_strlen(*str) - 1;
	while (a > 0 && lst.temp[1][a] == '2')
		a--;
	if (lst.temp[1][a] == 'P')
	{
		if (fork() == 0)
			get_pipe(fd, env);
		wait(NULL);
		close(fd[1]);
		close(g_data.flag[1]);
		close(g_data.flag[0]);
		read_line(fd[0], str);
		close(fd[0]);
	}
	free_temps(&lst);
}
