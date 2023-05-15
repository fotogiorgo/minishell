/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:10 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/15 14:52:11 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_chars_in_exit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return 2;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	exit_func(char **argv)
{
	int	i;

	i = 0;
	if (argv[1] != NULL)
	{
		write(1, "exit\n", 6);
		printf("minishell: exit: too many arguments\n");
		g_data.exit_code = 1;
		return ;
	}
	else
	{
		if (check_chars_in_exit(argv[0]) == 1)
			g_data.exit_code = ft_atoi(argv[0]) % 256;
		else if (check_chars_in_exit(argv[0]) == 0)
			g_data.exit_code = 255;
	}
	disable_enable_echoctl(1);
	write(2, "exit\n", 6);
	exit(g_data.exit_code);
	//kill(getppid(), SIGTSTP);
}
