/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 10:59:11 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/27 06:13:49 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spliter_error_syntax(int state)
{
	if (state == SIMPLE_Q)
		return (error_syntax("unexpected EOF while looking for matching `\''"));
	return (error_syntax("unexpected EOF while looking for matching `\"'"));
}

int	token_start_error_syntax(int curr_token)
{
	if (curr_token == DAND)
		return (error_unexpected_token("&&"));
	else if (curr_token == DOR)
		return (error_unexpected_token("||"));
	else if (curr_token == PIPE)
		return (error_unexpected_token("|"));
	else if (curr_token == EPAR)
		return (error_unexpected_token(")"));
	return (curr_token);
}

int	token_middle_error_syntax(int curr_token, int old)
{
	if (old < DAND && curr_token == RIN)
		return (error_unexpected_token("<"));
	else if (old < DAND && curr_token == DRIN)
		return (error_unexpected_token("<<"));
	else if (old < DAND && curr_token == ROUT)
		return (error_unexpected_token(">"));
	else if (old < DAND && curr_token == DROUT)
		return (error_unexpected_token(">>"));
	else if (old < DAND && curr_token == SPAR)
		return (error_unexpected_token("("));
	else if (old < DAND && curr_token == EPAR)
		return (error_unexpected_token(")"));
	else if (curr_token == DAND)
		return (error_unexpected_token("&&"));
	else if (curr_token == DOR)
		return (error_unexpected_token("||"));
	else if (curr_token == PIPE)
		return (error_unexpected_token("|"));
	return (curr_token);
}

int	token_epar_error_syntax(int curr, int old)
{
	if (old == RIN)
		return (error_unexpected_token(")"));
	else if (old == DRIN)
		return (error_unexpected_token(")"));
	else if (old == ROUT)
		return (error_unexpected_token(")"));
	else if (old == DROUT)
		return (error_unexpected_token(")"));
	else if (old == DAND)
		return (error_unexpected_token(")"));
	else if (old == DOR)
		return (error_unexpected_token(")"));
	else if (old == PIPE)
		return (error_unexpected_token(")"));
	else if (old == SPAR)
		return (error_unexpected_token(")"));
	return (curr);
}

int	token_last_error_syntax(int curr_token, int state)
{
	if (state != 0)
		return (error_unexpected_token("newline"));
	else if (curr_token == RIN)
		return (error_unexpected_token("newline"));
	else if (curr_token == DRIN)
		return (error_unexpected_token("newline"));
	else if (curr_token == ROUT)
		return (error_unexpected_token("newline"));
	else if (curr_token == DROUT)
		return (error_unexpected_token("newline"));
	else if (curr_token == DAND)
		return (error_unexpected_token("newline"));
	else if (curr_token == DOR)
		return (error_unexpected_token("newline"));
	else if (curr_token == PIPE)
		return (error_unexpected_token("newline"));
	return (curr_token);
}
