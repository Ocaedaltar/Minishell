/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_destroyer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:10:24 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/11 05:54:15 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaks_destroyer.h"

void	*ft_malloc_err(size_t size)
{
	static int	current = 0;
	static int	limit = -1;

	if (!DEBUG_MALLOC)
		return (ft_calloc(1, size));
	if (limit == -1)
		limit = ft_atoi(getenv("LIMIT"));
	if (current++ < limit)
		return (ft_calloc(1, size));
	else
	{
		fprintf(stderr, "Limit was set to %d\n", limit);
		return (NULL);
	}
}

void	ft_destroy_all(t_leaks **arr_ptr, int error, int exit_code)
{
	if (error != 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		ft_clearallocs(arr_ptr, free);
		exit(error);
	}
	ft_clearallocs(arr_ptr, free);
	exit(exit_code);
}

t_leaks	*ft_lstnew_alloc(void *content, t_leaks **arr_ptr)
{
	t_leaks	*new;

	errno = 0;
	new = ft_malloc_err(sizeof(t_leaks));
	if (new == NULL)
	{
		free(content);
		ft_destroy_all(arr_ptr, errno, 0);
	}
	ft_bzero(new, sizeof(t_leaks));
	new->content = content;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

void	ft_clearallocs(t_leaks **lst, void (*del)(void*))
{
	t_leaks	*lst_ptr;
	t_leaks	*prev_ptr;

	if (!lst || !*lst || !del)
		return ;
	lst_ptr = *lst;
	while (lst_ptr)
	{
		prev_ptr = lst_ptr;
		lst_ptr = lst_ptr->next;
		(*del)(prev_ptr->content);
		free(prev_ptr);
	}
	*lst = NULL;
}
