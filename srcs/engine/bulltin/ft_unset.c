/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 16:22:42 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/12 16:18:39 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *data)
{
	t_token	*argv;

	argv = data->args->next;
	while (argv)
	{
		ft_del_env(argv->str);
		argv = argv->next;
	}
	g_exit_status = 0;
}
