/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:32:09 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/27 05:40:50 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_split(t_token **lst, int type, char *str)
{
	int		i;
	int		j;
	char	*dst;

	j = 0;
	i = 0;
	while (str[j] && str[j] == SPLIT_CHAR)
		j++;
	while (str[j + i] && str[j + i] != SPLIT_CHAR)
		i++;
	if (i > 0)
	{
		dst = ft_substr(str, j, i);
		ft_absolute_line(&dst);
		ft_token_pushback(lst, ft_token_create(dst, type));
		ft_free_ptr((void **)&dst);
		if (type == 0)
			type = 1;
		ft_lst_split(lst, type, str + j + i);
	}
}

void	ft_insert_lst(t_token **new_lst, t_token **lst)
{
	t_token	*ptr_next;
	t_token	*ptr_prev;
	t_token	*ptr_lastlst;

	ptr_next = (*lst)->next;
	ptr_prev = (*lst)->prev;
	ptr_lastlst = ft_token_last((*new_lst));
	ft_token_delone(lst);
	if (!ptr_prev)
	{
		ptr_lastlst->next = (*lst);
		(*lst) = (*new_lst);
	}
	else
	{
		ptr_lastlst->next = ptr_next;
		ptr_prev->next = (*new_lst);
		(*new_lst)->prev = ptr_prev;
		(*lst) = (*new_lst);
	}
	if (ptr_next)
		ptr_next->prev = ptr_lastlst;
}
