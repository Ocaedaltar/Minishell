/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 07:46:52 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 15:42:01 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isopreating(char *str)
{
	unsigned long	i;
	static t_op		op[] = {{"<", RIN}, {"<<", DRIN}, {">", ROUT}, {"(", SPAR}
		, {">>", DROUT}, {"|", PIPE}, {"&&", DAND}, {"||", DOR}
		, {")", EPAR}};

	i = 0;
	while (i < sizeof(op) / sizeof(*op))
	{
		if (!ft_strcmp(str, op[i].str))
			return (op[i].ret);
		i++;
	}
	return (WRD);
}

/*
** Token type identification of each string, with the big part for
**	all major syntax error.
**
**	@param		str				The string to controll
**	@param		old				The Old type of the last string.
**	@param		index			Current index of the tab.
**	@param		size_max		Size of the tab.
**	@ret		The type of the string or an syntax error
*/

static int	search_token(char *str, int old, int index, int size_max)
{
	int			curr;
	static int	state = 0;

	curr = ft_isopreating(str);
	if (old > WRD && curr == WRD && (old == RIN || old == ROUT || old == DROUT))
		curr = FD;
	else if (old > WRD && curr == WRD && old == DRIN)
		curr = LIM;
	if (curr == SPAR)
		state++;
	if (curr == EPAR)
		state--;
	curr = checker_syntax(curr, old, index);
	if (curr != ERROR && index == size_max - 1)
		curr = token_last_error_syntax(curr, state);
	if (curr == ERROR)
		state = 0;
	return (curr);
}

/*
** Creation of the tokenizer linked list with a pushback
**	for all element of the tab_word, we creat a block in the lst
**
**	@param		tab_word		The tab of the cli splitted.
**	@param		size			Size of this tab.
**	@ret
*/

static t_token	*build_token_lst(char **tab_word, int size)
{
	t_token	*lst;
	int		old_type;
	int		type_token;
	int		index;

	index = 0;
	lst = NULL;
	old_type = -1;
	while (tab_word[index])
	{
		type_token = search_token(tab_word[index], old_type, index, size);
		if (type_token == ERROR)
			return (ft_return_clear(lst));
		ft_token_pushback(&lst, ft_token_create(tab_word[index++], type_token));
		old_type = type_token;
	}
	return (lst);
}

/*
** Set the commande type on the first argument type of the token lst
**	check if a syntax error on the list is existing
**
**	@param		lst		The lst at check and set.
**	@ret		the lst set or an syntax error.
*/

static t_token	*ft_set_cmd_token(t_token *lst)
{
	int		cmd_in_section;
	t_token	*ptr_tmp;

	ptr_tmp = lst;
	cmd_in_section = 0;
	while (ptr_tmp)
	{
		if (ptr_tmp->type == WRD && cmd_in_section == 0)
		{
			ptr_tmp->type = CMD;
			cmd_in_section = 1;
		}
		if (ptr_tmp->type == SPAR && cmd_in_section == 1)
		{
			error_unexpected_token(ptr_tmp->next->str);
			return (ft_return_clear(lst));
		}
		if (ptr_tmp->type == PIPE || ptr_tmp->type == DOR
			|| ptr_tmp->type == DAND)
			cmd_in_section = 0;
		ptr_tmp = ptr_tmp->next;
	}
	return (lst);
}

/*
** Manage the seconde step:
**	Build the tokenizer linked list with the tab
**	Do Basic syntax check and set up for the next step
**
**	@param		tab_word		The tab of the cli splitted.
**	@param		size_tab		Size of this tab.
**	@ret		goto -> shell_expension with the lst.
*/

void	shell_tokenizer(char **tab_word, int size_tab)
{
	t_token	*lst;

	lst = NULL;
	lst = build_token_lst(tab_word, size_tab);
	ft_clean_strs(tab_word);
	lst = ft_set_cmd_token(lst);
	if (lst && ft_check_parenthese(lst) != ERROR)
		shell_ast(lst);
}
