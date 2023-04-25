/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:12:09 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/25 19:05:00 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_single_quotes_string(char **temp_input, char **input_without_quotes)
{
	(*temp_input)++;
	while(**temp_input != 39 && **temp_input)
	{
		**input_without_quotes = **temp_input;
		(*temp_input)++;
		(*input_without_quotes)++;
	}
	(*temp_input)++;
}

void	add_double_quotes_string(char **temp_input, char **input_without_quotes)
{
	(*temp_input)++;
	while(**temp_input != 34 && **temp_input)
	{
		**input_without_quotes = **temp_input;
		(*temp_input)++;
		(*input_without_quotes)++;
	}
	(*temp_input)++;
}

char *return_input_without_quotes(char *input, int len)
{
	char	*input_without_quotes;
	char	*temp_input;
	int		i;

	i = 0;
	temp_input = input;
	input_without_quotes = (char *) malloc (sizeof(char) * len + 1);
	while (*temp_input != '\0')
	{
		if (*temp_input == 34)
			add_double_quotes_string(&temp_input, &input_without_quotes);
		else if (*temp_input == 39)
			add_single_quotes_string(&temp_input, &input_without_quotes);
		else
		{
		*input_without_quotes = *temp_input;
		temp_input++;
		input_without_quotes++;
		}
	}
	*input_without_quotes = '\0';
	input_without_quotes -= len;
	return input_without_quotes;
}

char	*remove_quotes(char *input)
{
	char	*removed_input;
	int		len;
	
	len = 0;
	if (!input)
		return (NULL);
	if (check_quotes(input) == -1)
		return (NULL);
	len = length_without_quotes(input);
	removed_input = return_input_without_quotes(input, len);
	return (removed_input);
}