/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:27:30 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/08 10:12:24 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_echo(char	**argv, int put_new_line, int arg_count, int i)
{
	if (put_new_line == 0)
	{
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			i++;
			if (i != arg_count)
				printf(" ");
		}
	}
	else if (put_new_line == 1)
	{
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			i++;
			if (i != arg_count)
				printf(" ");
		}
		printf("\n");
	}
}

int	check_new_line(char **argv)
{
	int i;
	int j;

	i = 0;
	while (ft_strncmp(argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (argv[i][j] == 'n' && argv[i][j] != '\0')
			j++;
		if (argv[i][j] == '\0')
			i++;
		else
			break;
	}
	return (i);
}

void	get_echo(char	**argv)
{
	int	put_new_line;
	int	arg_count;
	int	j;
	int	i;

	arg_count = 0;
	j = 0;
	put_new_line = 1;
	while (argv[arg_count] != NULL)
		arg_count++;
	if (arg_count > 0)
	{
		j = check_new_line(argv);
		if (j >= 1)
			put_new_line = 0;
	}
	print_echo(argv, put_new_line, arg_count, j);
	return ;
}