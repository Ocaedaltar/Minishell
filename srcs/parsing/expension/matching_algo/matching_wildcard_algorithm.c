/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching_wildcard_algorithm.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 09:42:45 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 16:00:31 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_was_start(char *line, char *need)
{
	int	i;

	i = 0;
	while (need[i] && line[i] == need[i])
		i++;
	if (!need[i])
		return (i);
	return (ERROR);
}

static int	ft_was_inside(char *line, int start, char *need)
{
	int	i;
	int	j;

	i = start;
	while (line[i])
	{
		j = 0;
		while (line[i + j] && line[i + j] == need[j])
		{
			j++;
			if (need[j] == '\0')
				return (i + j);
		}
		i++;
	}
	return (ERROR);
}

static int	match_algo_else(char *result, char *cond, char *next, int *index)
{
	if (!next || (next && ft_strcmp(next, "*")))
	{
		if (!ft_cmp_extension(result, cond))
			return (ERROR);
	}
	else if (next && !ft_strcmp(next, "*"))
	{
		*index = ft_was_inside(result, *index, cond);
		if (*index < 0)
			return (ERROR);
	}
	return (SUCCESS);
}

static char	*match_algo(char *p_use, char *line, char **cond)
{
	int		start;
	int		index;
	int		i;

	i = 0;
	index = 0;
	start = TRUE;
	while (cond[i] != NULL)
	{
		if (!ft_strcmp(cond[i], "*"))
			start = FALSE;
		else if (!ft_strcmp(cond[i], "/"))
			return (do_wildcard(ft_merge_slash(p_use, line), &cond[i + 1], 1));
		else if (start && ft_strcmp(cond[i], "*"))
			index = ft_was_start(line, cond[i]);
		else
			if (match_algo_else(line, cond[i], cond[i + 1], &index) == ERROR)
				return (NULL);
		if (index < 0)
			return (NULL);
		i++;
	}
	return (ft_merge_slash(p_use, line));
}

char	*do_wildcard(char *path, char **cond, int opt)
{
	char			*dst;
	struct dirent	*pdirent;
	DIR				*pdir;
	char			*tmp;

	dst = NULL;
	if (ft_opendir(&pdir, path) == ERROR)
		return (NULL);
	if (opt)
		path = ft_merge_slash(path, ft_strnew("/"));
	if (*cond == NULL)
		return (path);
	pdirent = readdir(pdir);
	while (pdirent != NULL)
	{
		tmp = ft_strnew(path);
		if (pdirent->d_name[0] != '.' || !ft_strcmp(cond[0], ".")
			|| !ft_strcmp(cond[0], ".."))
			dst = ft_merge_space(dst, match_algo(tmp, pdirent->d_name, cond));
		if (tmp)
			ft_free_ptr((void **)&tmp);
		pdirent = readdir(pdir);
	}
	closedir (pdir);
	return (dst);
}
