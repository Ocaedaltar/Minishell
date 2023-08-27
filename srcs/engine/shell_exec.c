/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 07:27:19 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/14 19:08:18 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec(t_cmd *data, char **env, t_ast *origin)
{
	char	*cmd;
	char	**args;

	cmd = NULL;
	signal_handling_default();
	args = ft_token_to_tab(data->args);
	if (args[0][0] != '.' && args[0][0] != '/')
		cmd = ft_isvalide_cmd(ft_merge("/", args[0]));
	else
	{
		if (ft_check_relative_binary(&cmd, args[0]) == ERROR)
			ft_destroy_exit(g_exit_status);
	}
	if (cmd)
	{
		if (data->input)
			dup2(data->input, STDIN_FILENO);
		if (data->output)
			dup2(data->output, STDOUT_FILENO);
		ft_ast_destroy(origin);
		execve(cmd, args, env);
	}
	else
		error_cmd_not_found(args[0]);
	ft_destroy_exit(g_exit_status);
}

static void	ft_prepare_exec(t_cmd *data, int *n_child, t_ast *origin)
{
	char	**env;
	pid_t	pid;

	ft_args_loader(&data->args);
	env = ft_lst_to_tab(ft_getallenv());
	if (data->args && ft_strlen(data->args->str) == 0)
	{
		g_exit_status = 127;
		write(STDERR_FILENO, "bash: ", 7);
		write(STDERR_FILENO, ": command not found\n", 21);
	}
	else if (data->args
		&& !ft_cmd_isbuiltin(data->args->str, data, origin, n_child))
	{
		signal_handling_reset();
		pid = fork();
		if (pid == 0)
			ft_exec(data, env, origin);
		ft_overwrite_redirection(data->input, data->output);
		(*n_child)++;
	}
	ft_overwrite_redirection(data->input, data->output);
	ft_clean_strs(env);
}

static void	search_exec(t_ast *data, int *n_child, t_ast *origin_data)
{
	if (data->left)
		search_exec(data->left, n_child, origin_data);
	if (data->type == DAND)
	{
		wait(&g_exit_status);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		if (g_exit_status == 0)
			search_exec(data->right, n_child, origin_data);
	}
	else if (data->type == DOR)
	{
		wait(&g_exit_status);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		if (g_exit_status != 0)
			search_exec(data->right, n_child, origin_data);
	}
	if (data->type == PIPE)
		search_exec(data->right, n_child, origin_data);
	if (data->type == CMD)
		ft_prepare_exec(data->cmd, n_child, origin_data);
}

void	shell_exec(t_ast *data)
{
	int		n_child;

	n_child = 0;
	search_exec(data, &n_child, data);
	while (n_child-- > 0)
		wait(&g_exit_status);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	signal_handling_register();
	ft_ast_destroy(data);
}
