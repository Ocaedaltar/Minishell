/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 05:40:31 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/12 15:23:48 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_parenthese(t_token *lst)
{
	int	state;
	int	state_cmd;

	state = 0;
	state_cmd = 0;
	while (lst)
	{
		if (lst->type == SPAR)
			state++;
		else if (lst->type == EPAR)
			state--;
		if (lst->type == CMD)
			state_cmd = state;
		if (lst->type == 1 && state_cmd != state)
			return (error_unexpected_token(lst->str));
		lst = lst->next;
	}
	return (SUCCESS);
}

static int	ft_check_ambigue(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SPLIT_CHAR)
		{
			error_syntax("*: ambiguous redirect");
			g_exit_status = 1;
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_expension_fd(char **str, int opt)
{
	if (do_split_quotes(str) == ERROR)
		return (ERROR);
	if (!opt)
		return (ft_check_ambigue(*str));
	(*str) = ft_absolute_line(str);
	return (SUCCESS);
}

int	error_permission_denied(char *file_name)
{
	write(STDERR_FILENO, "bash: ", 7);
	write(STDERR_FILENO, file_name, ft_strlen(file_name));
	write(STDERR_FILENO, ": Permission denied\n", 21);
	g_exit_status = 126;
	return (ERROR);
}

int	ft_check_relative_binary(char **cmd, char *arg)
{
	if (ft_check_file(arg) == ERROR)
		return (ERROR);
	if (isfile(arg) != TRUE)
	{
		write(STDERR_FILENO, "bash: ", 7);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": is a directory\n", 18);
		g_exit_status = 126;
		return (ERROR);
	}
	if (access(arg, X_OK))
		return (error_permission_denied(arg));
	(*cmd) = ft_strnew(arg);
	return (SUCCESS);
}
