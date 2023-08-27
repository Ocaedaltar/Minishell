/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_setpipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 13:27:53 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 14:53:39 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_search_loader(t_ast **data, int fd, int mode)
{
	if ((*data)->type == DAND || (*data)->type == DOR)
	{
		pipe_search_loader(&(*data)->left, fd, mode);
		if (mode == INPUT)
			pipe_search_loader(&(*data)->right, fd, mode);
	}
	else if ((*data)->type == PIPE)
	{
		if (mode == INPUT)
			pipe_search_loader(&(*data)->right, fd, mode);
		else
			pipe_search_loader(&(*data)->left, fd, mode);
	}
	else
	{
		(*data)->cmd->ispipe = 1;
		if (mode == INPUT)
			(*data)->cmd->output = fd;
		else if (mode == OUTPUT)
			(*data)->cmd->input = fd;
		else
			close(fd);
	}
}

static int	ft_pipe_loader(t_ast **data)
{
	int	fd[2];

	if (pipe(fd) == ERROR)
		return (ERROR);
	pipe_search_loader(&(*data)->left, fd[1], INPUT);
	pipe_search_loader(&(*data)->right, fd[0], OUTPUT);
	return (SUCCESS);
}

int	ft_ast_setpipe(t_ast **data)
{
	int	ret;

	ret = SUCCESS;
	if ((*data))
	{
		if ((*data)->type == PIPE)
			ret = ft_pipe_loader(data);
		if ((*data)->left)
			ret = ft_ast_setpipe(&(*data)->left);
		if ((*data)->right)
			ret = ft_ast_setpipe(&(*data)->right);
		if ((*data)->type == CMD)
			ret = ft_red_loader(&(*data)->cmd, (*data)->cmd->red);
	}
	return (ret);
}
