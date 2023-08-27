/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 02:44:29 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/10 22:46:39 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getenv.h"

/*
**	Main function, this is the Handler
*/

t_lst	**ft_envp(char **envp, char *toinsert, t_lst *newlst)
{
	static t_lst	*environement = NULL;

	if (envp != NULL)
		environement = ft_dtab_to_lst(envp);
	else if (toinsert != NULL)
		ft_lst_push_back(&environement, toinsert);
	else if (newlst != NULL)
		environement = newlst;
	return (&environement);
}

/*
**	Delete a var with his KEY if it exist
*/

void	ft_del_env(char *key)
{
	t_lst	*prev;
	t_lst	*env;

	env = ft_getallenv();
	prev = NULL;
	while (env)
	{
		if (ft_strlen(env->line) > ft_strlen(key))
		{
			if (ft_strncmp(env->line, key, ft_strlen(key)) == 0
				&& *(env->line + ft_strlen(key)) == '=')
			{
				if (prev)
					prev->next = env->next;
				else
					ft_envp(NULL, NULL, env->next);
				ft_free_ptr((void **)&env->line);
				ft_free_ptr((void **)&env);
				return ;
			}
		}
		prev = env;
		env = env->next;
	}
	return ;
}

/*
** Clone function of getenv
*/

char	*ft_getenv(char *key)
{
	t_lst	*env;

	env = ft_getallenv();
	while (env)
	{
		if (ft_strlen(env->line) > ft_strlen(key))
		{
			if (ft_strncmp(env->line, key, ft_strlen(key)) == 0
				&& *(env->line + ft_strlen(key)) == '=')
				return (env->line + ft_strlen(key) + 1);
		}
		env = env->next;
	}
	return (NULL);
}
