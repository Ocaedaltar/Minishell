/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 16:18:18 by rmechety          #+#    #+#             */
/*   Updated: 2021/09/12 16:18:23 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_too_many_args(int fd_out)
{
	write(fd_out, "exit\n", 6);
	write(fd_out, "bash: exit: too many arguments\n", 32);
	g_exit_status = 1;
	return ;
}

void	ft_exit(t_cmd *data)
{
	if (data->args->next)
	{
		if (data->args->next->next != NULL)
			return (exit_too_many_args(data->output));
		else
		{
			if (ft_isnumber(data->args->next->str))
			{
				write(data->output, "exit\n", 6);
				ft_destroy_exit(ft_atoi(data->args->next->str));
			}
			else
			{
				write(data->output, "exit\nbash: exit: ", 18);
				write(data->output, data->args->next->str,
					ft_strlen(data->args->next->str));
				write(data->output, ": numeric argument required\n", 29);
				ft_destroy_exit(255);
			}
		}
	}
	write(data->output, "exit\n", 6);
	ft_destroy_exit(0);
}
