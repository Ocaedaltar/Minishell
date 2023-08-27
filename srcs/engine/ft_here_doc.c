/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:16:17 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/12 16:18:55 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_clear_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	ft_free_ptr((void **)&line);
}

static void	heredoc_no_expension(t_cmd **data, char *limiter)
{
	char	*line;

	line = NULL;
	limiter = ft_remove_quotes(limiter);
	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(limiter, line))
		{
			ft_free_ptr((void **)&line);
			break ;
		}
		ft_print_clear_line((*data)->input, line);
	}
}

static void	heredoc_yes_expension(t_cmd **data, char *limiter)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(limiter, line))
		{
			ft_free_ptr((void **)&line);
			break ;
		}
		ft_expension_fd(&line, 1);
		ft_print_clear_line((*data)->input, line);
	}
}

int	ft_here_doc(t_cmd **data, char *limiter)
{
	ft_overwrite_redirection((*data)->input, 0);
	(*data)->input = ft_create_fd(PATH_HEREDOC, 0);
	if (limiter && limiter[0] == '"')
		heredoc_no_expension(data, limiter);
	else
		heredoc_yes_expension(data, limiter);
	close((*data)->input);
	(*data)->input = open(PATH_HEREDOC, O_RDONLY);
	if ((*data)->input == ERROR)
		return (ERROR);
	return (SUCCESS);
}
