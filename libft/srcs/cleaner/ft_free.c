/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:40:14 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/10 01:03:01 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Free l'entierter d'un tableau
**
**	@param		strs	le tableau a free
**	@ret		N/A
*/

void	ft_clean_strs(char **strs)
{
	int	index;

	index = 0;
	if (strs)
	{		
		while (strs[index])
		{
			ft_free_ptr((void **)&strs[index]);
			index++;
		}
		ft_free_ptr((void **)&strs);
	}
}
