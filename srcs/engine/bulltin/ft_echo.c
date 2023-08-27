/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:10:50 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/12 16:18:44 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_option(t_token **argv)
{
	int	i;
	int	opt;

	opt = 0;
	(*argv) = (*argv)->next;
	while ((*argv) && (*argv)->str[0] == '-')
	{
		i = 1;
		while ((*argv)->str[i] == 'n')
			i++;
		if ((*argv)->str[i] != 0)
			break ;
		if (i == 1)
			break ;
		opt = TRUE;
		(*argv) = (*argv)->next;
	}
	return (opt);
}

void	ft_echo(t_cmd *data)
{
	int		opt;
	t_token	*to_print;

	to_print = data->args;
	opt = ft_echo_option(&to_print);
	while (to_print)
	{
		write(data->output, to_print->str, ft_strlen(to_print->str));
		to_print = to_print->next;
		if (to_print)
			write(data->output, " ", 1);
	}
	if (!opt)
		write(data->output, "\n", 1);
	g_exit_status = 0;
}
