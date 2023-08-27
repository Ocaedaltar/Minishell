/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_destroyer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:25:51 by mlormois          #+#    #+#             */
/*   Updated: 2021/07/26 18:20:25 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaks_destroyer.h"

void	*ft_alloc(size_t size)
{
	void	*ptr;

	ptr = ft_alloc_mem(size, 0, NULL, 0);
	return (ptr);
}

void	ft_free_ptr(void **addr)
{
	ft_alloc_mem(0, 0, addr, 0);
}

void	ft_destroy_exit(int exit_code)
{
	ft_alloc_mem(0, 1, NULL, exit_code);
}
