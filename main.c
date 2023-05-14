/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:21:19 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/09 09:14:55 by kakumar          ###   ########.fr       */
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
void	ctrl_D_handler(t_argv_vec *argv)
{
	disable_enable_echoctl(1);
	write(1, "\033[1A", 5);
	write(1, "\033[11C", 6);
	write(1, "exit\n", 6);
	exit(1);
}

//buff is free'd in tokenize_input()
int	take_input(char *str, t_argv_vec *argv)
{
	char	*buff;

	buff = readline("minishell$ ");
	if (buff == NULL)
		ctrl_D_handler(argv);
	else
	{
		if (ft_strlen(buff) < 1)
		{
			free(buff);
			return (0);
		}
		add_history(buff);
		if (tokenize_input(buff, argv) == 0)
			return (0);
	}
	return(1);
}

void	init_data(t_argv_vec *argv, char **envp)
{
	data.argv = argv;
	data.num_of_env_var = 0;
	data.envp_list = NULL;
	data.envp_list = create_our_envp(envp);
	data.exit_code = 0;
	return ;
}

/* remember that after using the input free the entire argv
so it can be used agaain for the next readline*/
int main(int argc, char **argv1, char **envp)
{
	char		input_str[MAXIN];
	t_argv_vec	argv;
	
	(void) argv1;
	(void) argc;
	init_shell();
	init_data(&argv, envp);
	while (1)
	{
		if (!take_input(input_str, &argv)) // i changed this so always when something goes wrong we return 0
			continue;
		check_command_from_input(&argv);
		free_argv(&argv);
	}
}