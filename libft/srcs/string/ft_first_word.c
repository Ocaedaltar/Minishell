/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 14:25:44 by mlormois          #+#    #+#             */
/*   Updated: 2021/08/05 06:14:35 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_first_word(char *line)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	word = NULL;
	while (ft_iswhitespace(line[i]))
		i++;
	j = i;
	while (ft_isalnum(line[j]))
		j++;
	if (j > i)
		word = ft_substr(line, i, j);
	return (word);
}

char	*ft_first_word_dollar(char *line)
{
	char	*word;
	int		i;

	i = 0;
	word = NULL;
	while (line[i] != '$' && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (i)
		word = ft_substr(line, 0, i);
	return (word);
}
