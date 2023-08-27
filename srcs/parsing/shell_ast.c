/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 02:16:29 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 14:55:19 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_haveopp(t_token *lst)
{
	while (lst)
	{
		if (!(lst->type < DAND || lst->type >= SPAR))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static int	ft_build_child(t_ast **data, t_token *ptr_first)
{
	t_cmd	*new_cmd;

	new_cmd = NULL;
	if (ft_haveopp(ptr_first))
	{
		if (ft_ast_build(data, ptr_first) == ERROR)
			return (ERROR);
	}
	else
	{
		ft_cmd_create(&new_cmd, &ptr_first);
		(*data) = ft_ast_create(0, new_cmd);
	}
	return (SUCCESS);
}

static int	ft_build_parent(t_ast **data, t_token *lst_left, t_token *lst_right)
{
	(*data) = ft_ast_create(lst_right->type, NULL);
	lst_right->prev->next = NULL;
	lst_right->prev = NULL;
	ft_token_delone(&lst_right);
	if (ft_ast_build(&(*data)->left, lst_left) == ERROR)
		return (ERROR);
	if (ft_ast_build(&(*data)->right, lst_right) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ft_ast_build(t_ast **data, t_token *lst)
{
	t_token	*ptr_first;

	ptr_first = lst;
	if (lst && lst->type == SPAR)
	{
		ptr_first = lst->next;
		lst = ft_skip_parenthese(&lst);
	}
	while (lst && (lst->type < DAND || lst->type >= SPAR))
		lst = lst->next;
	if (lst)
	{
		if (ft_build_parent(data, ptr_first, lst) == ERROR)
			return (ERROR);
	}
	else
		if (ft_build_child(data, ptr_first) == ERROR)
			return (ERROR);
	return (SUCCESS);
}

void	shell_ast(t_token *lst)
{
	t_ast	*btree_ast;

	btree_ast = NULL;
	ft_ast_build(&btree_ast, lst);
	if (ft_ast_setpipe(&btree_ast) == ERROR)
		g_exit_status = 1;
	else
		shell_exec(btree_ast);
}
