/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 02:44:23 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/09 19:30:23 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_select_line(char *str, int i, int j, int opt)
{
	char	*tmp;
	char	*dst;

	tmp = NULL;
	if (j && !ft_strncmp("$?", str, 2))
	{
		dst = ft_itoa(g_exit_status);
		return (dst);
	}
	else if (j)
	{
		tmp = ft_first_word_dollar(str + j);
		dst = ft_strnew(ft_getenv(tmp));
		if (opt == 1)
			ft_negchar(&dst, ' ');
		ft_free_ptr((void **)&tmp);
		if (dst == NULL)
			dst = ft_strnew("");
		return (dst);
	}
	dst = ft_substr(str, 0, i + j);
	return (dst);
}

static int	ft_skip_rec_env(char *str, int j)
{
	int	i;

	i = 0;
	if (str[i + j] == '?')
		return (1);
	while (str[j + i] && str[j + i] != '$' && (ft_iswhitespace(str[j + i])
			|| (!ft_isalnum(str[j + i]) && str[j + i] != '_')))
		i++;
	while (str[j + i] && str[j + i] != '$' && !ft_iswhitespace(str[j + i])
		&& (ft_isalnum(str[j + i]) || str[j + i] == '_'))
		i++;
	return (i);
}

static int	ft_split_rec_env(char ***tab, char *str, int index, int opt)
{
	int	i;
	int	j;

	j = 0;
	if (str[j] && str[j] == '$')
		j++;
	i = ft_skip_rec_env(str, j);
	if (i > 0)
	{
		ft_split_rec_env(tab, str + j + i, index + 1, opt);
		(*tab)[index] = ft_select_line(str, i, j, opt);
	}
	else if (j)
	{
		ft_split_rec_env(tab, str + j + i, index + 1, opt);
		(*tab)[index] = ft_strnew("$");
	}
	else
	{
		(*tab) = (char **)ft_alloc(sizeof(char *) * (index + 1));
		(*tab)[index] = NULL;
	}
	return (SUCCESS);
}

static char	**ft_split_env(char *str, int opt)
{
	char	**split;

	split = NULL;
	if (!str)
		return (NULL);
	ft_split_rec_env(&split, str, 0, opt);
	return (split);
}

char	*ft_add_variable(char *line, int opt)
{
	char	**split;

	split = ft_split_env(line, opt);
	ft_free_ptr((void **)&line);
	line = NULL;
	line = ft_strsjoin(split, ft_strslen(split));
	ft_clean_strs(split);
	return (line);
}
