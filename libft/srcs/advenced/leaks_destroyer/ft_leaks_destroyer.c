/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leaks_destroyer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:27:54 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/17 17:58:48 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaks_destroyer.h"

static void	ft_lstadd_back(t_leaks **alst, t_leaks *new)
{
	t_leaks	*tmp;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
	new->next = NULL;
}

static void	ft_lstdelnode(t_leaks **elem, void (*del)(void *))
{
	t_leaks	*tmp;

	if (del == NULL || *elem == NULL)
		return ;
	tmp = *elem;
	if ((*elem)->previous == NULL && (*elem)->next == NULL)
		*elem = NULL;
	else if ((*elem)->previous == NULL && (*elem)->next != NULL)
	{
		*elem = (*elem)->next;
		(*elem)->previous = NULL;
	}
	else if ((*elem)->previous != NULL && (*elem)->next == NULL)
	{
		*elem = (*elem)->previous;
		(*elem)->next = NULL;
	}
	else if ((*elem)->previous != NULL && (*elem)->next != NULL)
	{
		*elem = (*elem)->previous;
		(*elem)->next = (*elem)->next->next;
		(*elem)->next->previous = (*elem);
	}
	del(tmp->content);
	free(tmp);
}

static t_leaks	**find_addr(t_leaks **lst, void *addr)
{
	t_leaks	**node_addr;

	while (*lst)
	{
		if (addr == (*lst)->content)
		{
			node_addr = lst;
			return (node_addr);
		}
		*lst = (*lst)->next;
	}
	return (NULL);
}

static void	*ft_free(t_leaks **pointers, void **addr)
{
	t_leaks	**tmp;
	t_leaks	*cursor;

	tmp = NULL;
	if (*pointers && *addr == (*pointers)->content)
		ft_lstdelnode(pointers, free);
	else
	{
		cursor = *pointers;
		tmp = find_addr(&cursor, *addr);
		if (tmp)
		{
			ft_lstdelnode(tmp, free);
			*addr = NULL;
		}
	}
	return (NULL);
}

void	*ft_alloc_mem(size_t size, int done, void **addr, int exit_code)
{
	static t_leaks	*pointers = NULL;
	void			*ptr;

	if (done == 1)
		ft_destroy_all(&pointers, 0, exit_code);
	if (addr != NULL)
		return (ft_free(&pointers, addr));
	ptr = ft_malloc_err(size);
	if (ptr == NULL)
		ft_destroy_all(&pointers, errno, 0);
	else
		ft_lstadd_back(&pointers, ft_lstnew_alloc(ptr, &pointers));
	return (ptr);
}
