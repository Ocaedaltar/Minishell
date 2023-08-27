/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extension.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 00:23:23 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/04 12:34:49 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compare l'extension d'un fichier avec celle attendue, retournera 1 si
** identique, sinon 0. 
**
**	@param	file	le fichier a comparer
**	@param	ext		l'extension de reference
**	@ret	0/1
*/

int	ft_cmp_extension(char *file, char *ext)
{
	int	len_file;
	int	len_ext;

	len_file = ft_strlen(file);
	len_ext = ft_strlen(ext);
	while (len_file-- > 0 && len_ext-- > 0 && file[len_file] == ext[len_ext])
		if (len_ext == 0)
			return (TRUE);
	return (FALSE);
}
