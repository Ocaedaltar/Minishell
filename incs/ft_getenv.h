/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 02:39:06 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/15 18:41:00 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETENV_H
# define FT_GETENV_H

# include "stdlib.h"
# include "string.h"
# include "minishell.h"

typedef struct s_lst	t_lst;

struct		s_lst
{
	char	*line;
	t_lst	*next;
};

t_lst	*ft_new_lst_elem(char *data);
void	ft_lst_push_back(t_lst **slst, char *data);
t_lst	*ft_dtab_to_lst(char **tab);

void	ft_init_env(int ac, char **av, char **env);
void	ft_add_env(char *to_add);
t_lst	*ft_getallenv(void);
t_lst	**ft_getaddenv(void);

t_lst	**ft_envp(char **envp, char *toinsert, t_lst *newlst);
void	ft_del_env(char *key);
char	*ft_getenv(char *key);

#endif
