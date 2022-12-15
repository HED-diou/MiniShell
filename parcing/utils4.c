/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nramadan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 21:02:40 by nramadan          #+#    #+#             */
/*   Updated: 2022/06/10 20:17:10 by nramadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_sig(int fd, char *c)
{
	if (fd <= 0)
		return ;
	read(fd, c, 1);
}

int	ft_numcount(unsigned int a, int sign)
{
	unsigned int	size;

	size = 0;
	if (a == 0)
		size++;
	if (sign < 0)
		size++;
	while (a > 0)
	{
		a = a / 10;
		size++;
	}
	return (size);
}

char	*ft_numberfill(char *str, unsigned int n, int size, int sign)
{
	str[size] = '\0';
	size -= 1;
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (sign < 0)
		str[0] = '-';
	while (n > 0)
	{
		str[size--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int num)
{
	char			*str;
	int				size;
	int				sign;
	unsigned int	n;

	sign = 1;
	if (num < 0)
	{
		n = num * (-1);
		sign = -sign;
	}
	else
		n = num;
	size = ft_numcount(n, sign);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str = ft_numberfill(str, n, size, sign);
	return (str);
}
