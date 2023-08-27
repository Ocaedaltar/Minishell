/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:09:52 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/12 16:18:46 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_no_arg(void)
{
	char	*arg;

	arg = ft_getenv("HOME");
	if (!arg)
	{
		write(STDERR_FILENO, "bash: cd: HOME not set\n", 24);
		g_exit_status = 1;
	}
	else if (chdir(arg) == ERROR)
	{
		write(STDERR_FILENO, "bash: cd: ", 11);
		perror(arg);
		g_exit_status = 1;
	}
	else
		ft_swap_env_pwd(arg);
}

static void	ft_cd_minus(char *arg)
{
	if (!ft_strcmp(arg, "-"))
	{
		arg = ft_getenv("OLDPWD");
		if (!arg)
		{
			write(STDERR_FILENO, "bash: cd: OLDPWD not set\n", 24);
			g_exit_status = 1;
		}
		if (chdir(arg) == ERROR)
		{
			write(STDERR_FILENO, "bash: cd: ", 11);
			perror(arg);
			g_exit_status = 1;
		}
		else
			ft_swap_env_pwd(arg);
	}
	else
	{
		write(STDERR_FILENO, "bash: cd: ", 11);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": invalid option\n", 18);
		g_exit_status = 1;
	}
}

static void	ft_cd_basic(char *arg)
{
	char	*pwd;

	if (chdir(arg) == ERROR)
	{
		write(STDERR_FILENO, "bash: cd: ", 11);
		perror(arg);
		g_exit_status = 1;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		arg = ft_merge_slash(NULL, pwd);
		free(pwd);
		ft_swap_env_pwd(arg);
	}
}

static void	ft_cd_yes_arg(char *arg)
{
	if (arg[0] == '-')
		ft_cd_minus(arg);
	else
	{
		if (arg[0] == '/')
		{
			if (chdir(arg) == ERROR)
			{
				write(STDERR_FILENO, "bash: cd: ", 11);
				perror(arg);
				g_exit_status = 1;
			}
			else
				ft_swap_env_pwd(arg);
		}
		else
			ft_cd_basic(arg);
	}
}

void	ft_cd(t_cmd *data)
{
	char	*arg;

	arg = NULL;
	if (data->args->next)
		arg = data->args->next->str;
	if (!arg)
		ft_cd_no_arg();
	else
		ft_cd_yes_arg(arg);
}
