/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 23:11:50 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/06 23:12:35 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Atoi lite, car on check avant de l'appeler si les arg sont valide
**
** @param	str			 La string a transformer en int
** @return	(res * flag) La valeur numerique de la str
*/

int	ft_atoi(char *str)
{
	int	index;
	int	res;
	int	flag;

	index = 0;
	res = 0;
	flag = 1;
	if (str[index] == '-')
	{
		flag *= -1;
		index++;
	}
	while (str[index])
	{
		res *= 10;
		res += str[index] - 48;
		index++;
	}
	return (res * flag);
}
