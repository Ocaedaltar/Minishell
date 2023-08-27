/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 02:53:31 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 15:36:43 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isfile(const char *name)
{
	DIR	*directory;

	directory = opendir(name);
	if (directory != NULL)
	{
		closedir(directory);
		return (0);
	}
	if (errno == ENOTDIR)
		return (1);
	return (-1);
}

int	ft_check_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
	{
		g_exit_status = 127;
		write(STDERR_FILENO, "bash: ", 7);
		perror(filename);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

void	ft_overwrite_redirection(int input, int output)
{
	if (input)
		close(input);
	if (output != 1)
		close(output);
}

int	ft_open_fd(char *file, int flag, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, flag);
	else
		fd = open(file, flag, mode);
	if (fd != ERROR)
		return (fd);
	return (ERROR);
}

int	ft_create_fd(char *file, int mode)
{
	int	fd;

	if (!mode)
		fd = ft_open_fd(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = ft_open_fd(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}
