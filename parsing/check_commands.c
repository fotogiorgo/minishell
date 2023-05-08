/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:33:18 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/08 10:26:42 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_command_from_input(t_argv_vec	*argv)
{
	if (ft_strncmp_case_ins(argv->argv[0], "pwd", 3) == 0)
		get_pwd(argv->argv[0]);
	else if (ft_strncmp_case_ins(argv->argv[0], "echo", 4) == 0)
		get_echo(&argv->argv[1]);
	else if (ft_strncmp_case_ins(argv->argv[0], "cd", 2) == 0)
		get_pwd(argv->argv[0]);
	else if (ft_strncmp_case_ins(argv->argv[0], "export", 6) == 0)
		export_var(&argv->argv[1]);
	else if (ft_strncmp_case_ins(argv->argv[0], "unset", 5) == 0)
		get_pwd(argv->argv[0]);
	else if (ft_strncmp_case_ins(argv->argv[0], "env", 3) == 0)
		get_all_env(&data->envp_list);
	else if (ft_strncmp_case_ins(argv->argv[0], "exit", 3) == 0)
		exit_func();
	else
		printf("minishell: %s: command not found\n", argv->argv[0]);
	return ;
}