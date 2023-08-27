/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_getenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 02:40:18 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/10 22:46:09 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getenv.h"

t_lst	*ft_new_lst_elem(char *data)
{
	t_lst	*new;

	new = ft_alloc(sizeof(t_lst));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->line = data;
	return (new);
}

void	ft_lst_push_back(t_lst **slst, char *data)
{
	t_lst	*lst;

	lst = *slst;
	if (lst == NULL)
	{
		*slst = ft_new_lst_elem(data);
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = ft_new_lst_elem(data);
}

t_lst	*ft_dtab_to_lst(char **tab)
{
	t_lst	*lst;

	lst = NULL;
	while (*tab != NULL)
	{
		ft_lst_push_back(&lst, *tab);
		tab++;
	}
	return (lst);
}
