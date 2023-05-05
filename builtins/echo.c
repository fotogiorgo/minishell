/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:27:30 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/03 15:25:43 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_echo(t_argv_vec *argv, int put_new_line, int i)
{
	if (put_new_line == 0)
	{
		while (i < argv->curr)
		{
			printf("%s", argv->argv[i]);
			i++;
			if (i != argv->curr)
				printf(" ");
		}
	}
	else if (put_new_line == 1)
	{
		while (i < argv->curr)
		{
			printf("%s", argv->argv[i]);
			i++;
			if (i != argv->curr)
				printf(" ");
		}
		printf("\n");
	}
}

int	check_new_line(t_argv_vec *argv)
{
	int i;
	int j;

	i = 1;
	while (ft_strncmp(argv->argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (argv->argv[i][j] == 'n' && argv->argv[i][j] != '\0')
			j++;
		if (argv->argv[i][j] == '\0')
			i++;
		else
			break;
	}
	return (i);
}

void	get_echo(t_argv_vec *argv)
{
	int	put_new_line;
	int	i;

	i = 1;
	put_new_line = 1;
	if (argv->curr > 1)
	{
		i = check_new_line(argv);
		if (i > 1)
			put_new_line = 0;
	}
	print_echo(argv, put_new_line, i);
	return ;
}