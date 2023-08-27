/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 12:03:50 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/03 18:23:29 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ft_ast_create(int type, t_cmd *elem_cli)
{
	t_ast	*btree_ast;

	btree_ast = ft_alloc(sizeof(t_ast));
	btree_ast->type = type;
	btree_ast->cmd = elem_cli;
	btree_ast->right = NULL;
	btree_ast->left = NULL;
	return (btree_ast);
}

void	ft_ast_destroy(t_ast *data)
{
	if (data)
	{
		if (data->right)
			ft_ast_destroy(data->right);
		if (data->left)
			ft_ast_destroy(data->left);
		if (data->cmd)
			ft_cmd_destroy(data->cmd);
		ft_free_ptr((void **)&data);
	}
}
