/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 01:56:38 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/31 17:10:18 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_search_path(char **dst, char *line)
{
	int	i;
	int	last_slash;

	i = 0;
	(*dst) = NULL;
	last_slash = 0;
	while (line[i] && line[i] != '*')
	{
		if (line[i] == '/')
			last_slash = i + 1;
		i++;
	}
	if (last_slash)
		(*dst) = ft_substr(line, 0, last_slash);
	return (last_slash);
}

static int	ft_goto_end_condition(char *line, int start)
{
	int	i;

	i = 0;
	if (line[i + start] == '/' || line[i + start] == '*')
		return (1);
	while (line[start + i])
	{
		if (line[start + i] == '*')
			break ;
		else if (line[start + i] == '/')
			break ;
		i++;
	}
	return (i);
}

static int	ft_split_wildcard_rec(char ***tab, char *line, int index)
{
	int	i;
	int	j;
	int	ret;

	j = 0;
	while ((line[j] == '*' && line[j + 1] == '*')
		|| (line[j] == '/' && line[j + 1] == '/'))
		j++;
	i = ft_goto_end_condition(line, j);
	if (i < 0)
		return (ERROR);
	else if (i > 0)
	{
		ret = ft_split_wildcard_rec(tab, line + j + i, index + 1);
		if (ret == ERROR)
			return (ERROR);
		(*tab)[index] = ft_substr(line, j, i);
		return (ret);
	}
	else
	{
		(*tab) = (char **)ft_alloc(sizeof(char *) * (index + 1));
		(*tab)[index] = NULL;
	}
	return (index);
}

char	*expension_wildcard(char *line)
{
	char	*path;
	char	**split;
	int		index;
	char	*dst;

	if (ft_strchr(line, '*'))
	{
		index = ft_search_path(&path, line);
		ft_split_wildcard_rec(&split, line + index, 0);
		dst = do_wildcard(path, split, 0);
		if (dst)
		{
			ft_free_ptr((void **)&line);
			line = dst;
		}
		ft_clean_strs(split);
	}
	return (line);
}
