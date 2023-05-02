/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:21:19 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/02 19:50:52 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void init_shell(void)
{
	init_terminal();
	init_signals();
	write(1, "\n\n\n\n Minishell by jofoto and kakumar \n\n\n\n", 42);
}

/* \033[11C moves cursor right 11 spots */
/* \033[1A moves cursor up 1 spot */
void	ctrl_D_handler(void)
{
	disable_enable_echoctl(1);
	write(1, "\033[1A", 5);
	write(1, "\033[11C", 6);
	write(1, "exit\n", 6);
	exit(1);
}

//buff is free'd in tokenize_input()
int	take_input(char *str, t_argv_vec argv)
{
	char	*buff;

	buff = readline("minishell$ ");
	if (buff == NULL)
		ctrl_D_handler();
	else
	{
		add_history(buff);
		if(tokenize_input(buff, &argv) == 0)
			return (0);
		/* here you can take the argv and cleanse it (remove the
		quotes that have to be removed, add env variables)*/
	}
	return(1);
}

/* remember that after using the input free the entire argv
so it can be used agaain for the next readline*/
int main(void)
{
	char		input_str[MAXIN];
	t_argv_vec	argv;

	init_shell();
	while (1)
	{
		if (!take_input(input_str, argv)) // i changed this so always when something goes wrong we return 0
			continue;
		//check_command_from_input(input_str);
	}
}