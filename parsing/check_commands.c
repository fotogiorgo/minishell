/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:33:18 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/13 11:02:51 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_command_from_input(t_argv_vec	*argv)
{
	if (ft_strncmp_case_ins(argv->argv[0], "pwd", 4) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(argv->argv[0], "echo", 5) == 0)
		get_echo(&argv->argv[1]);
	else if (ft_strncmp_case_ins(argv->argv[0], "cd", 3) == 0)
		get_cd(&argv->argv[1]);
	else if (ft_strncmp_case_ins(argv->argv[0], "export", 7) == 0)
		export_var(&argv->argv[1]);
	else if (ft_strncmp_case_ins(argv->argv[0], "unset", 6) == 0)
		unset_var(&argv->argv[1]);
	else if (ft_strncmp_case_ins(argv->argv[0], "env", 4) == 0)
		get_all_env();
	else if (ft_strncmp_case_ins(argv->argv[0], "exit", 5) == 0)
		exit_func();
	else
		printf("minishell: %s: command not found\n", argv->argv[0]);
	return ;
}