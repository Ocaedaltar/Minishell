/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:54:12 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 12:31:45 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compare deux string l'une a l'autre, retournera la difference entre le
** le caractere differents ou le dernier. 
**
**	@param	s1		string 1
**	@param	s2		string 2
**	@ret	int		la difference entre deux char.
*/

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/* Compare deux string l'une a l'autre, retournera la difference entre le
** le caractere differents ou le dernier jusqu'a (n) caractere. 
**
**	@param	str			la chaine checkée
**	@param	to_find		la chaine recherchée
**	@param	n			le nombre de caractere comaparé
**	@ret	int		la difference entre deux char.
*/

char	*ft_strnstr(char *str, char *to_find, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == to_find[i] && i < n)
	{
		i++;
		if (i == n)
			return (str);
	}
	return (NULL);
}

/* Compte le nombre de caractere dans une string
**
**	@param 	s	la chaine a compter
**	@ret	i	le nombre de caractere de s
*/

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_end_word(char *str, int start)
{
	int	index;

	index = 0;
	while (str[start + index] && !ft_iswhitespace(str[start + index])
		&& (str[start + index] != '$' && index != 0))
	{
		index++;
	}
	return (start + index);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && *(s1 + i) && *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return (*(s1 + i) - *(s2 + i));
		i++;
	}
	return (0);
}
