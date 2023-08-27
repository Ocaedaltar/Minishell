/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 21:46:25 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/06 15:07:03 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checker_syntax(int curr, int old, int index)
{
	if (curr != ERROR && index == 0)
		curr = token_start_error_syntax(curr);
	if (curr != ERROR && old > LIM && old < EPAR)
		curr = token_middle_error_syntax(curr, old);
	if (curr != ERROR && curr == EPAR)
		curr = token_epar_error_syntax(curr, old);
	return (curr);
}

void	error_cmd_not_found(char *cmd)
{
	g_exit_status = 127;
	write(STDERR_FILENO, "bash: ", 7);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 21);
	ft_destroy_exit(g_exit_status);
}

int	error_syntax(char *message)
{
	g_exit_status = ERROR_STATUS;
	write(STDERR_FILENO, "bash: ", 7);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 2);
	return (ERROR);
}

int	error_unexpected_token(char *token)
{
	g_exit_status = ERROR_STATUS;
	write(STDERR_FILENO, "bash: syntax error near unexpected token `", 43);
	write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, "`\n", 3);
	return (ERROR);
}

void	*ft_return_clear(t_token *data)
{
	ft_token_destroy(data);
	return (NULL);
}
