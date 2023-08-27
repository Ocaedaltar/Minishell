/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 07:24:04 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/14 19:07:40 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_secure_readline(void)
{
	char	*line_read;
	char	*secure_line;

	line_read = NULL;
	secure_line = NULL;
	line_read = readline(DISPLAY_PROMPT);
	if (line_read)
	{
		secure_line = ft_alloc(ft_strlen(line_read) + 1);
		secure_line = ft_strcpy(secure_line, line_read);
		free(line_read);
	}
	return (secure_line);
}

static void	ft_loop(void)
{
	char	*line_read;

	while (1)
	{
		line_read = ft_secure_readline();
		if (line_read == NULL)
			break ;
		else if (line_read && *line_read)
		{
			signal_handling_reset();
			add_history(line_read);
			shell_spliter(line_read);
		}
		else if (ft_strlen(line_read) == 0)
			g_exit_status = 127;
		ft_free_ptr((void **)&line_read);
		line_read = NULL;
	}
	write(STDIN_FILENO, "exit\n", 6);
}

int	main(int ac, char **av, char **envp)
{
	ft_init_env(ac, av, envp);
	signal_handling_register();
	ft_loop();
	rl_clear_history();
	ft_destroy_exit(g_exit_status);
	return (0);
}
