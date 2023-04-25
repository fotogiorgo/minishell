/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:57:28 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/25 18:46:59 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_double_quotes(char *input)
{
	int	i;
	char *temp;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 34)
		{
			i++;
			temp = ft_strchr(&input[i], 34);
			if (temp == 0)
			{
				printf("minishell$ Error: Unclosed quotes\n");
				return (-1);
			}
			else
				i += (temp - &input[i]);
		}
		i++;
	}
	return (0);
}

//ascii value for ' is 39
int	check_single_quotes(char *input)
{
	int	i;
	char *temp;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 39)
		{
			i++;
			temp = ft_strchr(&input[i], 39);
			if (temp == 0)
			{
				printf("minishell$ Error: Unclosed quotes\n");
				return (-1);
			}
			else
				i += (temp - &input[i]);
		}
		i++;
	}
	return (0);
}