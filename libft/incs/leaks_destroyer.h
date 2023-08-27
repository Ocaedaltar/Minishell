/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_destroyer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:11:31 by mlormois          #+#    #+#             */
/*   Updated: 2021/07/30 18:15:06 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAKS_DESTROYER_H
# define LEAKS_DESTROYER_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>

# include "libft.h"

# ifndef DEBUG_MALLOC
#  define DEBUG_MALLOC 0
# endif

typedef struct s_leaks	t_leaks;

struct					s_leaks
{
	void			*content;
	t_leaks			*previous;
	t_leaks			*next;
};

void		*ft_alloc_mem(size_t size, int done, void **addr, int exit_code);
void		*ft_alloc(size_t size);
void		ft_destroy_exit(int exit_code);
void		ft_free_ptr(void **addr);

t_leaks		*ft_lstnew_alloc(void *content, t_leaks **arr_ptr);
void		ft_clearallocs(t_leaks **lst, void (*del)(void*));
void		ft_destroy_all(t_leaks **arr_ptr, int error, int exit_code);
void		*ft_malloc_err(size_t size);

#endif
