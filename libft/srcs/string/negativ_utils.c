/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negativ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:51:20 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/11 00:14:56 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_absolute_line(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == -32)
			(*line)[i] *= -1;
		i++;
	}
	return ((*line));
}

void	ft_negchar(char **line, char c)
{
	int	i;

	i = 0;
	while ((*line) && (*line)[i])
	{
		if ((*line)[i] == c)
			(*line)[i] *= -1;
		i++;
	}
}

void	ft_neglastchar(char **line, char c)
{
	int	i;

	i = 0;
	while ((*line)[i])
		i++;
	if (i > 0 && (*line)[i - 1] == c)
		(*line)[i - 1] *= -1;
}
