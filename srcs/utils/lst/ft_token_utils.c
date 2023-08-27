/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:40:12 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/08 01:30:22 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_last(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*ft_token_first(t_token *lst)
{
	while (lst && lst->prev)
		lst = lst->prev;
	return (lst);
}

t_token	*ft_skip_parenthese(t_token **lst)
{
	int	state;

	state = 1;
	ft_token_delone(lst);
	while ((*lst) && state != 0)
	{
		if ((*lst)->type == SPAR)
			state++;
		else if ((*lst)->type == EPAR)
			state--;
		if (state != 0)
			(*lst) = (*lst)->next;
	}
	ft_token_delone(lst);
	return ((*lst));
}
