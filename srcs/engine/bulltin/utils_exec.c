/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:20:34 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 15:48:04 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_isbuiltin(char *cmd, t_cmd *data, t_ast *origin, int *n_child)
{
	static const t_bultin	bultin[] = {{"echo", &ft_echo}, {"cd", &ft_cd},
		{"pwd", &ft_pwd}, {"export", &ft_export}, {"unset", &ft_unset},
		{"env", &ft_env}, {"exit", &ft_exit}};
	unsigned long			i;

	i = 0;
	while (i < sizeof(bultin) / sizeof(*bultin))
	{
		if (!ft_strcmp(cmd, bultin[i].str))
		{
			if (data->ispipe == 0)
				bultin[i].ft(data);
			else
				ft_builtin_forked(data, bultin[i].ft, origin, n_child);
			return (SUCCESS);
		}
		i++;
	}
	return (FALSE);
}

void	ft_swap_env_pwd(char *arg)
{
	ft_del_env("OLDPWD");
	ft_add_env(ft_merge_slash("OLDPWD=", ft_getenv("PWD")));
	ft_del_env("PWD");
	ft_add_env(ft_merge_slash("PWD=", arg));
	g_exit_status = 0;
}

static char	*valide_cmd_return(char *binary, char **strs, char *ret)
{
	ft_free_ptr((void **)binary);
	ft_clean_strs(strs);
	return (ret);
}

char	*ft_isvalide_cmd(char *binary)
{
	char	*path;
	char	*cmd_path;
	char	**path_dirs;
	int		i;

	i = 0;
	path = ft_getenv("PATH");
	path_dirs = ft_split(path, ':');
	if (path_dirs == NULL)
		return (NULL);
	ft_free_ptr((void **)&path);
	while (path_dirs && path_dirs[i])
	{
		cmd_path = ft_merge(path_dirs[i], binary);
		if (!access(cmd_path, X_OK))
			return (valide_cmd_return(binary, path_dirs, cmd_path));
		ft_free_ptr((void **)cmd_path);
		i++;
	}
	return (valide_cmd_return(binary, path_dirs, NULL));
}

int	ft_args_loader(t_token **args)
{
	t_token	*ptr_tmp;
	t_token	*tmp_next;
	t_token	*new_lst;

	ptr_tmp = (*args);
	while (ptr_tmp)
	{
		new_lst = NULL;
		tmp_next = ptr_tmp->next;
		if (ptr_tmp->type < RIN)
		{
			if (ft_expension_apply(&new_lst, &ptr_tmp) == ERROR)
			{
				ft_token_destroy(ft_token_first(ptr_tmp));
				return (ERROR);
			}
			ft_absolute_line(&ptr_tmp->str);
		}
		if (tmp_next == NULL)
			break ;
		ptr_tmp = tmp_next;
	}
	(*args) = ft_token_first(ptr_tmp);
	return (SUCCESS);
}
