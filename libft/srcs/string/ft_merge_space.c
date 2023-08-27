/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 09:52:57 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 15:40:57 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Malloc une chaine de caractere de la taille des deux string en argument
**  Copy ces deux chaines dans la string nouvellement crée
**
** @param		s1		
** @param		s2		
** @return		dst		the new string concated
*/

static void	ft_cat_free(char *dst, char *str)
{
	ft_strcat(dst, str);
	ft_free_ptr((void **)&str);
}

char	*ft_merge_space(char *s1, char *s2)
{
	char	*dst;
	int		len_s1;
	int		len_s2;
	int		space;

	if (!s2)
		return (s1);
	space = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 && len_s2)
		space = 1;
	dst = (char *)ft_alloc(sizeof(char) * (len_s1 + len_s2 + space + 1));
	if (s1)
		ft_cat_free(dst, s1);
	if (s2)
	{
		if (space)
		{
			ft_strcat(dst, " ");
			ft_neglastchar(&dst, ' ');
		}
		ft_cat_free(dst, s2);
	}
	return (dst);
}

char	*ft_merge_slash(char *s1, char *s2)
{
	char	*dst;
	int		len_s1;
	int		len_s2;

	if (!s2)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *)ft_alloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (s1)
		ft_cat_free(dst, s1);
	if (s2)
		ft_cat_free(dst, s2);
	return (dst);
}

char	*ft_merge(char *s1, char *s2)
{
	char	*dst;
	int		len_s1;
	int		len_s2;

	dst = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *)ft_alloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (dst == NULL)
		return (NULL);
	ft_strcat(dst, s1);
	ft_strcat(dst, s2);
	return (dst);
}
