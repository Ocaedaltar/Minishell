/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulltin_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:49:43 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 15:30:59 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_forked(t_cmd *data, void (*ft)(t_cmd *),
	t_ast *origin, int *n_child)
{
	pid_t	pid;

	(*n_child)++;
	signal_handling_reset();
	pid = fork();
	if (pid == 0)
	{
		signal_handling_default();
		if (data->input)
			dup2(data->input, STDIN_FILENO);
		if (data->output)
			dup2(data->output, STDOUT_FILENO);
		ft(data);
		ft_ast_destroy(origin);
		ft_destroy_exit(g_exit_status);
	}
	ft_overwrite_redirection(data->input, data->output);
}
