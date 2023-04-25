/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_len_without_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:48:29 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/25 18:40:50 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int double_quote_length(char *input)
{
	int	i;

	i = 0;
	while (input[i] != 34 && input[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	single_quote_length(char *input)
{
	int i;

	i = 0;
	while (input[i] != 39 && input[i] != '\0')
	{
		i++;
	}
	return (i);
}
//ascii value for ' is 39
int	length_without_quotes(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 39)
		{
			i++;
			len += single_quote_length(&input[i]);
			i += single_quote_length(&input[i]) + 1;
		}
		else if (input[i] == 34)
		{
			i++;
			len += double_quote_length(&input[i]);
			i += double_quote_length(&input[i]) + 1;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}