/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_spliter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 08:57:35 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 15:42:39 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Skip with space and return index at the next char of the string line.
*/

static int	ft_goto_next_word(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (!ft_iswhitespace(line[index]))
			break ;
		index++;
	}
	return (index);
}

/*	Split The Word respectng the quoting rules for syntax error,
** 		check if the char isnt a Oppertator
**
**	@param		line		The cli to split.
**	@param		start		index for skip withespace.
**	@ret		index of the end of word, or A Syntax Error
*/

static int	ft_goto_end_word(char *line, int start)
{
	int	index;
	int	state;

	state = NORMAL;
	index = ft_ismetachar(line, start);
	if (index != 0)
		return (index);
	while (line[start + index])
	{
		if (state == NORMAL && (ft_iswhitespace(line[start + index])
				|| ft_ismetachar(line, start + index)))
			break ;
		else if (state == SIMPLE_Q && line[start + index] == '\'')
			state = NORMAL;
		else if (state == NORMAL && line[start + index] == '\'')
			state = SIMPLE_Q;
		else if (state == DOUBLE_Q && line[start + index] == '"')
			state = NORMAL;
		else if (state == NORMAL && line[start + index] == '"')
			state = DOUBLE_Q;
		index++;
	}
	if (state != NORMAL)
		return (spliter_error_syntax(state));
	return (index);
}

/*	Basic Split recursiv for cli of minishell, (skip withespace)
** 		check if the word is a metachar and split it if its TRUE
**		care of the respect of Quoting Rules
**
**	@param		tab			Address of the tab.
**	@param		line		The cli to split.
**	@param		index		index for the malloc at the end.
**	@ret		SUCCESS or ERROR
*/

static int	split_cli_rec(char ***tab, char *line, int index)
{
	int	i;
	int	j;

	j = ft_goto_next_word(line);
	i = ft_goto_end_word(line, j);
	if (i < 0)
		return (ERROR);
	else if (i > 0)
	{
		if (split_cli_rec(tab, line + j + i, index + 1) == ERROR)
			return (ERROR);
		(*tab)[index] = ft_substr(line, j, i);
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

/*
** Split the line give by readline for each Opperator
**
**	@param		line		The cli give by readline.
**	@ret		split		The line splited
*/

static char	**split_cli(char *line)
{
	char	**split;

	split = NULL;
	if (split_cli_rec(&split, line, 0) == ERROR)
		return (NULL);
	return (split);
}

/*
** Manage the first step:
**	Split Words and Operator obeying the quoting rules
**	- if the tab exist we continue the parsing
**
**	@param		line		The cli give by readline.
**	@ret		goto -> shell_tokenizer with tab_word.
*/
void	shell_spliter(char *line)
{
	char	**tab_word;

	tab_word = NULL;
	tab_word = split_cli(line);
	ft_free_ptr((void **)&line);
	if (tab_word)
		shell_tokenizer(tab_word, ft_strslen(tab_word));
}
