/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 14:11:42 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/09 19:26:30 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_goto_end_state(char *line, int start)
{
	int	i;
	int	state;

	i = 0;
	state = NORMAL;
	if (line[start + i] == '\'')
		state = SIMPLE_Q;
	else if (line[start + i] == '"')
		state = DOUBLE_Q;
	while (line[start + i])
	{
		if (i != 0 && state != DOUBLE_Q && line[start + i] == '\'')
			break ;
		if (i != 0 && state != SIMPLE_Q && line[start + i] == '\"')
			break ;
		i++;
	}
	if (state != NORMAL)
		i++;
	return (i);
}

static int	split_quotes_rec(char ***tab, char *line, int index)
{
	int	i;
	int	ret;

	i = ft_goto_end_state(line, 0);
	if (i == ERROR)
		return (ERROR);
	else if (i > 0)
	{
		ret = split_quotes_rec(tab, line + i, index + 1);
		if (ret == ERROR)
			return (ERROR);
		(*tab)[index] = ft_substr(line, 0, i);
		return (ret);
	}
	else
	{
		(*tab) = (char **)ft_alloc(sizeof(char *) * (index + 1));
		(*tab)[index] = NULL;
	}
	return (index);
}

int	do_split_quotes(char **str)
{
	char	**split;
	int		nb;
	int		i;

	i = 0;
	split = NULL;
	if (!(*str))
		return (ERROR);
	nb = split_quotes_rec(&split, (*str), 0);
	if (nb == ERROR)
		return (ERROR);
	ft_free_ptr((void **)str);
	while (i < nb)
	{
		split[i] = do_expension(split[i]);
		i++;
	}
	(*str) = ft_strsjoin(split, i);
	(*str) = expension_wildcard((*str));
	ft_clean_strs(split);
	return (SUCCESS);
}

int	ft_expension_apply(t_token **new_lst, t_token **ptr_tmp)
{
	if (do_split_quotes(&(*ptr_tmp)->str) == ERROR)
		return (ERROR);
	if (ft_strchr((*ptr_tmp)->str, SPLIT_CHAR))
	{
		ft_lst_split(new_lst, (*ptr_tmp)->type, (*ptr_tmp)->str);
		ft_insert_lst(new_lst, ptr_tmp);
	}
	return (SUCCESS);
}

void	shell_expension(t_token *lst)
{
	t_token	*ptr_tmp;
	t_token	*tmp_next;
	t_token	*new_lst;

	ptr_tmp = lst;
	while (ptr_tmp)
	{
		new_lst = NULL;
		tmp_next = ptr_tmp->next;
		if (ptr_tmp->type < RIN)
		{
			if (ft_expension_apply(&new_lst, &ptr_tmp) == ERROR)
				return (ft_token_destroy(ft_token_first(ptr_tmp)));
			ft_absolute_line(&ptr_tmp->str);
		}
		if (tmp_next == NULL)
			break ;
		ptr_tmp = tmp_next;
	}
	lst = ft_token_first(ptr_tmp);
}
