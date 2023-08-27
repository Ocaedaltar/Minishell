/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:03:03 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/12 16:18:51 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *data)
{
	t_lst	*env;

	env = ft_getallenv();
	while (env)
	{
		if (ft_strchr(env->line, '='))
		{
			write(data->output, env->line, ft_strlen(env->line));
			write(data->output, "\n", 2);
		}
		env = env->next;
	}
	g_exit_status = 0;
}
