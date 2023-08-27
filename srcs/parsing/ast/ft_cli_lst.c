/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cli_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 20:21:39 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 15:37:40 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirection_loader(t_cmd **data, t_token *lst)
{
	while (lst)
	{
		if (lst->type >= RIN && lst->type <= DROUT)
		{
			ft_token_pushback(&(*data)->red,
				ft_token_create(lst->next->str, lst->type));
		}
		lst = lst->next;
	}
}

static void	ft_arguments_loader(t_cmd **data, t_token *lst)
{
	while (lst)
	{
		if (lst->type == CMD || lst->type == WRD)
		{
			ft_token_pushback(&(*data)->args,
				ft_token_create(lst->str, lst->type));
		}
		lst = lst->next;
	}
}

int	ft_cmd_create(t_cmd **data, t_token **lst)
{
	(*data) = (t_cmd *)ft_alloc(sizeof(t_cmd));
	(*data)->output = 1;
	ft_redirection_loader(data, *lst);
	ft_arguments_loader(data, *lst);
	ft_token_destroy(*lst);
	return (SUCCESS);
}

void	ft_cmd_destroy(t_cmd *data)
{
	if (data->args)
		ft_token_destroy(data->args);
	if (data->red)
		ft_token_destroy(data->red);
	ft_overwrite_redirection(data->input, data->output);
	ft_free_ptr((void **)&data);
}
