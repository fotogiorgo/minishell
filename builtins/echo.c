/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:27:30 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/26 12:32:16 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_echo(char *input)
{
	int		put_new_line;
	int		num_of_quotes;
	char	*removed_quotes_input;
	char	*orig_input;
	char	*wrong_input;
	
	if (!input)
		return ;
	orig_input = input;
	input += 4;
	if (*input != ' ')
	{
		wrong_input = return_wrong_input(orig_input);
		printf("minishell: %s: command not found\n", wrong_input);
		free(wrong_input);
		return ;
	}
	input++;
	put_new_line = 1;
	num_of_quotes = 0;
	if (ft_strncmp(input, "-n", 2) == 0)
	{
		put_new_line = 0;
		input += 3;
	}
	removed_quotes_input = remove_quotes(input);
	if (put_new_line == 0 && removed_quotes_input)
	{
		printf("%s", removed_quotes_input);
		free(orig_input);
		free(removed_quotes_input);
		return ;
	}
	else if (put_new_line == 1 && removed_quotes_input)
	{
		printf("%s\n", removed_quotes_input);
		free(orig_input);
		free(removed_quotes_input);
		return ;
	}
	return ;
}