/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_funs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:01:53 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/08 12:46:22 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	record_history(char *str)
{
	int	fd;

	add_history(str);
	fd = open("./cache/history", O_CREAT | O_WRONLY | O_APPEND, \
			S_IRUSR | S_IWUSR);
	if (fd <= 0 || ft_strlen(str) == 0)
		return ;
	add_history(str);
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	close(fd);
}

int	get_line(int fd, char **str)
{
	int	a;
	int	b;

	a = 1;
	b = 0;
	*str = NULL;
	while (a != 0)
	{
		ft_realloc(str, 1);
		a = read(fd, (*str + b), 1);
		if ((*str)[b] && (*str)[b] == '\n')
		{
			(*str)[b] = '\0';
			break ;
		}
		b++;
	}
	return (a);
}

void	charge_history(void)
{
	char	*str;
	int		fd;
	int		a;
	int		b;

	a = 1;
	fd = open("./cache/history", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR);
	if (fd <= 0)
		return ;
	while (a != 0)
	{
		str = NULL;
		b = 0;
		a = get_line(fd, &str);
		add_history(str);
		free(str);
	}
}
