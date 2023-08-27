/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 03:06:56 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/01 03:08:20 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lst_to_tab_rec(char ***tab, t_lst *data, int index)
{
	if (data)
	{
		if (ft_lst_to_tab_rec(tab, data->next, index + 1) == ERROR)
			return (ERROR);
		(*tab)[index] = ft_strnew(data->line);
	}
	else
	{
		(*tab) = (char **)ft_alloc(sizeof(char *) * (index + 1));
		if ((*tab) == NULL)
			return (ERROR);
		(*tab)[index] = NULL;
	}
	return (SUCCESS);
}

char	**ft_lst_to_tab(t_lst *data)
{
	char	**tab;

	tab = NULL;
	ft_lst_to_tab_rec(&tab, data, 0);
	return (tab);
}

static int	ft_token_to_tab_rec(char ***tab, t_token *data, int index)
{
	if (data && (data->type == CMD || data->type == WRD))
	{
		ft_token_to_tab_rec(tab, data->next, index + 1);
		(*tab)[index] = ft_strnew(data->str);
	}
	else if (data)
		ft_token_to_tab_rec(tab, data->next, index);
	else
	{
		(*tab) = (char **)ft_alloc(sizeof(char *) * (index + 1));
		(*tab)[index] = NULL;
	}
	return (SUCCESS);
}

char	**ft_token_to_tab(t_token *data)
{
	char	**tab;

	tab = NULL;
	ft_token_to_tab_rec(&tab, data, 0);
	return (tab);
}
