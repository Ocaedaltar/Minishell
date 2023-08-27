/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:59:10 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/28 15:14:19 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_quotes(char *line)
{
	char	*dst;

	dst = ft_substr(line, 1, ft_strlen(line) - 2);
	ft_free_ptr((void **)&line);
	return (dst);
}

char	*ft_double_quotes_expension(char *line)
{
	int	i;

	i = 0;
	line = ft_remove_quotes(line);
	if (!line)
		return (ft_strnew(""));
	if (ft_strchr(line, '$'))
	{
		while (line[i])
		{
			if (line[i] == '$')
			{
				line = ft_add_variable(line, FALSE);
				break ;
			}
			i++;
		}
	}
	ft_negchar(&line, '*');
	return (line);
}

char	*ft_normal_expension(char *line)
{
	int	i;

	i = 0;
	if (ft_strchr(line, '$'))
	{
		while (line[i])
		{
			if (line[i] == '$')
			{
				line = ft_add_variable(line, TRUE);
				break ;
			}
			i++;
		}
	}
	return (line);
}

char	*do_expension(char *line)
{
	if (line[0] == '\'')
	{
		line = ft_remove_quotes(line);
		ft_negchar(&line, '*');
	}
	else if (line[0] == '\"')
		line = ft_double_quotes_expension(line);
	else
		line = ft_normal_expension(line);
	return (line);
}
