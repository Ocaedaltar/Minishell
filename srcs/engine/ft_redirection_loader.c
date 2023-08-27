/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_loader.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 03:35:03 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 14:50:15 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_rin_loader(t_cmd **data, char *file_name)
{
	ft_overwrite_redirection((*data)->input, 0);
	(*data)->input = 0;
	if (ft_check_file(file_name) == ERROR)
		return (ERROR);
	(*data)->input = open(file_name, O_RDONLY);
	if ((*data)->input == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	ft_rout_loader(t_cmd **data, char *file_name)
{
	ft_overwrite_redirection(0, (*data)->output);
	(*data)->output = ft_create_fd(file_name, 0);
	if ((*data)->output == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	ft_drout_loader(t_cmd **data, char *file_name)
{
	ft_overwrite_redirection(0, (*data)->output);
	(*data)->output = ft_create_fd(file_name, 1);
	if ((*data)->output == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ft_red_loader(t_cmd **data, t_token *redirection)
{
	int	ret;

	ret = 0;
	while (redirection)
	{
		if (redirection->type != DRIN)
		{
			if (ft_expension_fd(&redirection->str, 0) == ERROR)
				return (ERROR);
		}
		if (redirection->type == RIN)
			ret = ft_rin_loader(data, redirection->str);
		else if (redirection->type == DRIN)
			ret = ft_here_doc(data, redirection->str);
		else if (redirection->type == ROUT)
			ret = ft_rout_loader(data, redirection->str);
		else if (redirection->type == DROUT)
			ret = ft_drout_loader(data, redirection->str);
		if (ret == ERROR)
			return (ERROR);
		redirection = redirection->next;
	}
	return (SUCCESS);
}
