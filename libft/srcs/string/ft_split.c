/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 12:37:10 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/10 01:00:22 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_rec(char ***tab, char *str, int index, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[j] && str[j] == c)
		j++;
	while (str[j + i] && str[j + i] != c)
		i++;
	if (i > 0)
	{
		if (ft_split_rec(tab, str + j + i, index + 1, c) == ERROR)
			return (ERROR);
		(*tab)[index] = ft_substr(str, j, i);
	}
	else
	{
		(*tab) = (char **)ft_alloc(sizeof(char *) * (index + 1));
		if ((*tab) == NULL)
			return (ERROR);
		(*tab)[index] = NULL;
	}
	return (SUCCESS);
}

char	**ft_split(char *str, char c)
{
	char	**split;

	split = NULL;
	if (!str)
		return (NULL);
	if (ft_split_rec(&split, str, 0, c) == ERROR)
		return (NULL);
	return (split);
}
