/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:40:49 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/09 19:31:23 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsjoin(char **strs, int len_array)
{
	int		i;
	int		len;
	char	*dst;
	int		dst_index;
	int		str_index;

	i = 0;
	dst = NULL;
	len = 0;
	while (i < len_array)
		len += ft_strlen(strs[i++]);
	dst = ft_alloc(sizeof(char) * (len + 1));
	i = 0;
	dst_index = 0;
	while (i < len_array)
	{
		str_index = 0;
		while (strs[i] && strs[i][str_index])
			dst[dst_index++] = strs[i][str_index++];
		i++;
	}
	dst[dst_index] = '\0';
	return (dst);
}
