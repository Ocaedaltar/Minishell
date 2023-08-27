/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 08:01:28 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/27 10:40:02 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_create(char *str, int type)
{
	t_token	*lst;

	lst = (t_token *)ft_alloc(sizeof(t_token));
	if (lst == NULL)
		ft_destroy_exit(258);
	lst->str = ft_strnew(str);
	lst->type = type;
	lst->prev = NULL;
	lst->next = NULL;
	return (lst);
}

void	ft_token_pushback(t_token **lst, t_token *new_elem)
{
	t_token	*tmp;

	if (*lst == NULL)
	{
		*lst = new_elem;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_elem;
	new_elem->prev = tmp;
	new_elem->next = NULL;
}

void	ft_token_delone(t_token **elem)
{
	t_token	*tmp;

	if (*elem == NULL)
		return ;
	tmp = *elem;
	if ((*elem)->prev == NULL && (*elem)->next == NULL)
		*elem = NULL;
	else if ((*elem)->prev == NULL && (*elem)->next != NULL)
	{
		*elem = (*elem)->next;
		(*elem)->prev = NULL;
	}
	else if ((*elem)->prev != NULL && (*elem)->next == NULL)
	{
		*elem = (*elem)->prev;
		(*elem)->next = NULL;
	}
	else if ((*elem)->prev != NULL && (*elem)->next != NULL)
	{
		*elem = (*elem)->prev;
		(*elem)->next = (*elem)->next->next;
		(*elem)->next->prev = (*elem);
	}
	ft_free_ptr((void **)&tmp->str);
	ft_free_ptr((void **)&tmp);
}

void	ft_token_destroy(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		lst->prev = NULL;
		lst->type = 0;
		ft_free_ptr((void **)&lst->str);
		ft_free_ptr((void **)&lst);
		lst = tmp;
	}
}
