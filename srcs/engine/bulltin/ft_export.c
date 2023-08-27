/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:22:25 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/12 16:18:31 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_valide_export(char *str)
{
	char	*line;
	char	**tab;
	int		i;

	i = 0;
	line = str;
	tab = (char **)ft_alloc(sizeof(char *) * 4);
	tab[3] = NULL;
	while (line[i] && (line[i] != '=' || line[0] == '='))
		i++;
	tab[0] = ft_substr(line, 0, i);
	if (line[i] && line[i] == '=')
		tab[1] = ft_strnew("=");
	if (line[i])
		tab[2] = ft_strnew(line + i);
	return (tab);
}

static int	ft_isvalid_identifier(char *identifier)
{
	int	i;

	i = 0;
	if (!identifier)
		return (FALSE);
	if (ft_isdigit(identifier[0]))
		return (FALSE);
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_print_allenv(t_cmd *data)
{
	t_lst	*allenv;

	allenv = ft_getallenv();
	while (allenv)
	{
		write(data->output, "declare -x ", 12);
		write(data->output, allenv->line, ft_strlen(allenv->line));
		write(data->output, "\n", 2);
		allenv = allenv->next;
	}
	return (0);
}

static int	ft_export_env(t_token *argv)
{
	int		ret;
	char	**export_arg;

	while (argv)
	{
		export_arg = ft_split_valide_export(argv->str);
		if (!ft_isvalid_identifier(export_arg[0]))
		{
			write(STDERR_FILENO, "bash: '", 7);
			write(STDERR_FILENO, export_arg[0],
				ft_strlen(export_arg[0]));
			write(STDERR_FILENO, "': not a valid identifier\n", 27);
			ret = 1;
		}
		else
		{
			if (export_arg[1])
				ft_del_env(export_arg[0]);
			ft_add_env(ft_strnew(argv->str));
			ret = 0;
		}
		ft_clean_strs(export_arg);
		argv = argv->next;
	}
	return (ret);
}

void	ft_export(t_cmd *data)
{
	t_token	*argv;
	int		ret;

	ret = 0;
	argv = data->args->next;
	if (argv)
	{
		if (argv->str[0] == '-')
		{
			write(STDERR_FILENO, "bash: '", 8);
			write(STDERR_FILENO, argv->str, ft_strlen(argv->str));
			write(STDERR_FILENO, ": invalid option\n", 18);
			ret = 1;
		}
		else
			ret = ft_export_env(argv);
	}
	else
		ret = ft_print_allenv(data);
	g_exit_status = ret;
}
