/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:21:19 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/25 21:22:16 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void init_shell(void)
{
	printf("\n\n\n\n Minishell by jofoto and kakumar \n\n\n\n");
}

void	ctrl_D_handler(void)
{
	write(1, "\033[1A", 5);
	write(1, "\033[11C", 6);
	write(1, "exit\n", 6);
	exit(1);
}

int	take_input(char *str)
{
	char	*buff;
	size_t	len;
	
	buff = readline("minishell$ ");
	if (buff == NULL)
		ctrl_D_handler();
	len = ft_strlen(buff);
	if (len != 0)
	{
		add_history(buff);
		ft_strlcpy(str, buff, len + 1);
		free(buff);
		rl_on_new_line();
		return (0);
	}
	else
	{
		free(buff);
		rl_on_new_line();
		return (1);
	}
}

int main(void)
{
	char input_str[MAXIN];
	
	init_shell();
	init_signals();
	while (1)
	{
		if (take_input(input_str))
			continue;
		check_command_from_input(input_str);
	}
}