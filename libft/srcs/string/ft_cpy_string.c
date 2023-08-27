/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:42:22 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/27 09:56:23 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Malloc une chaine de caracter et copie celle passer en argument
**
** @param	str		la chaine a crée
** @return	dst		la nouvelle chaine crée (mallocé)
*/

char	*ft_strnew(char *str)
{
	char	*dst;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	dst = (char *)ft_alloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dst)
		return (NULL);
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
** Copie a string in another, DST should be malloced!
**
** @param	dst		the string to modify
** @param	src		the source string to copie
** @return	dst		the copie of the source
*/

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
** Add src in dst, at the end of dst
** NOTE : dst is malloc with the size of the 2 string len
**
** @param		dst		destination string
** @param		src		source string
** @return		dst		the string concated
*/

char	*ft_strcat(char *dst, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (dst);
	while (dst[i])
		i++;
	while (*src)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (dst);
}

/* Malloc une chaine de caractere de la taille LEN, a partir de l'index START
**	Copie les caractere entre Start et Len dans cette nouvelle chaine
**
** @param		s
** @param		start
** @param		len
** @return		dst		the new string (Malloc)
*/

char	*ft_substr(char *s, int start, int len)
{
	char	*dest;
	size_t	i;

	if (!s || len == 0)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		return (NULL);
	dest = ft_alloc(sizeof(*s) * (len + 1));
	while (len && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}
