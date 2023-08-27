/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:24:30 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/12 16:18:34 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	write(data->output, cwd, ft_strlen(cwd));
	write(data->output, "\n", 2);
	g_exit_status = 0;
}
