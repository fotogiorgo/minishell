/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:27:30 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/17 14:57:53 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_echo(char	**argv, int put_new_line, int i)
{
	if (!argv[i])
		return ;
	if (put_new_line == 0)
	{
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			i++;
			if (argv[i] != NULL)
				printf(" ");
		}
	}
	else if (put_new_line == 1)
	{
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			i++;
			if (i < g_data.argv->curr)
				printf(" ");
		}
		printf("\n");
	}
}

int	check_new_line(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (argv[i][j] == 'n' && argv[i][j] != '\0')
			j++;
		if (argv[i][j] == '\0')
			i++;
		else
			break ;
	}
	return (i);
}

void	get_echo(char	**argv)
{
	int	put_new_line;
	int	j;
	int	i;

	g_data.exit_code = 0;
	j = 0;
	put_new_line = 1;
	if (argv[0] != NULL)
	{
		j = check_new_line(argv);
		if (j >= 1)
			put_new_line = 0;
	}
	if (argv[0] == NULL || argv[0][0] == '\0')
	{
		printf("\n");
		return ;
	}
	print_echo(argv, put_new_line, j);
	return ;
}
