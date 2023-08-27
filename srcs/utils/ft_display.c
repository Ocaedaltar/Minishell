/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 08:49:46 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/10 22:00:37 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ast_display(t_ast *data)
{
	if (data)
	{
		printf("\ntype: %2d\n", data->type);
		if (data->cmd)
			ft_cmd_display(data->cmd);
		if (data->left)
			ft_ast_display(data->left);
		if (data->right)
			ft_ast_display(data->right);
	}
}

static void	ft_red_display(t_token *data)
{
	printf("red:\n");
	while (data)
	{
		if (data->type == RIN)
			printf("type : <");
		else if (data->type == DRIN)
			printf("type : <<");
		else if (data->type == ROUT)
			printf("type : >");
		else if (data->type == DROUT)
			printf("type : >>");
		printf(" : %s\n", data->str);
		data = data->next;
	}
	printf("\n");
}

void	ft_cmd_display(t_cmd *data)
{
	if (data)
	{
		if (data->input || data->output)
			printf("  input: %d\n  output: %d\n", data->input, data->output);
		if (data->args)
		{
			printf("CMD -> %s\n", data->args->str);
			printf("%s:\n", "arg");
			while (data->args)
			{
				printf("%s\n", data->args->str);
				data->args = data->args->next;
			}
			printf("\n");
		}
		if (data->red)
			ft_red_display(data->red);
	}
}

void	ft_token_display(t_token *lst)
{
	printf("\nDisplay LST TOKEN:\n");
	while (lst)
	{
		printf("type : %2d -> %s\n", lst->type, lst->str);
		lst = lst->next;
	}
	printf("\n");
}

void	ft_strs_display(char **tab_word)
{
	int	index;

	index = 0;
	while (tab_word[index])
	{
		printf("%d -> %s\n", index, tab_word[index]);
		index++;
	}
}
