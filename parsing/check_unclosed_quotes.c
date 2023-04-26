/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:57:28 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/26 12:18:07 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_double_quotes(char *input)
{
	int	i;
	char *temp;

	i = 0;
	if (input[i] == 34 && input[i] != '\0')
	{
		i++;
		temp = ft_strchr(&input[i], 34);
		if (temp == 0)
		{
			printf("minishell$ Error: Unclosed double quotes\n");
			return (-1);
		}
		else
		{
			i += (temp - &input[i]) + 1;
			return (i);
		}
	}
	return (0);
}

int	check_single_quotes(char *input)
{
	int	i;
	char *temp;

	i = 0;
	if (input[i] == 39 && input[i] != '\0')
	{
		i++;
		temp = ft_strchr(&input[i], 39);
		if (temp == 0)
		{
			printf("minishell$ Error: Unclosed single quotes\n");
			return (-1);
		}
		else
		{
			i += (temp - &input[i]) + 1;
			return (i);
		}
	}
	return (0);
}

int	check_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 34)
			if (check_double_quotes(&input[i]) == -1)
				return (-1);
			else
				i += check_double_quotes(&input[i]);
		else if(input[i] == 39)
			if (check_single_quotes(&input[i]) == -1)
				return (-1);
			else
				i += check_single_quotes(&input[i]);
		else
			i++;
	}
	return (0);
}