/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:35:25 by mlormois          #+#    #+#             */
/*   Updated: 2021/07/01 18:21:11 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Test a char for differents value
**
** @param	c			The char tested
** @return	TRUE/FALSE
*/

int	ft_iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
