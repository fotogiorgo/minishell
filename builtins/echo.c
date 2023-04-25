/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:27:30 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/25 19:06:21 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_echo(char *input)
{
	int		put_new_line;
	int		num_of_quotes;
	char	*removed_quotes_input;
	
	if (!input)
		return ;
	input += 5;
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
		free(removed_quotes_input);
		return ;
	}
	else if (put_new_line == 1 && removed_quotes_input)
	{
		printf("%s\n", removed_quotes_input);
		free(removed_quotes_input);
		return ;
	}
	return ;
}