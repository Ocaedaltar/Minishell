/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_getenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 02:42:07 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/10 22:27:35 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getenv.h"

int	g_exit_status = 0;

/*
**	Init the handler
**
*/
void	ft_init_env(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_envp(env, NULL, NULL);
}

/*
**	Adding an environement var to the handler
**	to_add est de la forme "TEST=MONSIEUR"
*/
void	ft_add_env(char *to_add)
{
	ft_envp(NULL, to_add, NULL);
}

/*
**	give the address of the list which contain env var
*/
t_lst	**ft_getaddenv(void)
{
	return (ft_envp(NULL, NULL, NULL));
}

/*
**	give the list which contain env var
*/
t_lst	*ft_getallenv(void)
{
	return (*ft_envp(NULL, NULL, NULL));
}
