/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 13:42:42 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/10 01:41:03 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_gnl_rec(int fd, char **line, int index)
{
	int		ret;
	char	buf;

	ret = read(fd, &buf, 1);
	if (ret == -1)
		return (-1);
	if (ret == 1 && buf != '\n')
	{
		ret = ft_gnl_rec(fd, line, index + 1);
		if (ret == -1)
			return (-1);
		(*line)[index] = buf;
	}
	else
	{
		(*line) = (char *)ft_alloc(sizeof(char) * (index + 1));
		if (!(*line))
			return (-1);
		(*line)[index] = '\0';
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	return (ft_gnl_rec(fd, line, 0));
}
