/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:10 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/17 14:58:07 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_chars_in_exit(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!str)
		return (2);
	while (str[i] != '\0')
	{
		if (str[i] == '+' || str[i] == '-')
		{
			i++;
			counter++;
		}
		if (ft_isdigit(str[i]) == 0 || counter > 1 || str[i] == '\0')
		{
			printf("minishell: exit: %s: numeric argument required\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	exit_func(char **argv)
{
	int	i;

	g_data.exit_code = 0;
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
		i = check_chars_in_exit(argv[0]);
		if (i == 0)
			g_data.exit_code = ft_atoi(argv[0]) % 256;
		else if (i == 1)
			g_data.exit_code = 255;
		else
			g_data.exit_code = 0;
	}
	disable_enable_echoctl(1);
	write(2, "exit\n", 6);
	exit(g_data.exit_code);
	//kill(getppid(), SIGTSTP);
}
