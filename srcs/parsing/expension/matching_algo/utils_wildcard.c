/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 13:15:42 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 13:33:00 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_opendir(DIR **pdir, char *path)
{
	if (!path)
		(*pdir) = opendir("./");
	else
		(*pdir) = opendir(path);
	if (!(*pdir))
		return (ERROR);
	return (SUCCESS);
}
