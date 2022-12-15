/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 22:20:35 by hed-diou          #+#    #+#             */
/*   Updated: 2022/06/07 13:18:24 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len )
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	if (!little || len <= 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		tmp = i;
		while (big[tmp] == little[j] && little[j] != '\0')
		{
			if (little[j + 1] == '\0' && tmp < len)
				return ((char *)&big[i]);
			j++;
			tmp++;
		}
		i++;
	}
	return (0);
}
