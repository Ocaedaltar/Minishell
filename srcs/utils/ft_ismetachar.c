/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismetachar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 13:34:38 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/27 13:15:42 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ismetachar(char *line, int start)
{
	int			meta_one;
	int			meta_two;
	static char	metachar[] = " ()<>|&";

	meta_one = ft_strchr_num(metachar, line[start]);
	if (meta_one > 0)
	{
		if (line[start] != '(' && line[start] != ')')
		{		
			meta_two = ft_strchr_num(metachar, line[start + 1]);
			if (meta_one == meta_two)
				return (2);
		}
		return (1);
	}
	return (0);
}
