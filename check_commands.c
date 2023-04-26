/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:33:18 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/26 10:51:20 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	check_echo

void	check_command_from_input(char *input)
{
	if (ft_strncmp_case_ins(input, "pwd", 3) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(input, "echo", 4) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(input, "cd", 2) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(input, "export", 6) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(input, "unset", 5) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(input, "env", 3) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(input, "exit", 3) == 0)
		get_pwd();
	else
		printf("minishell: %s: command not found\n", input);
	return ;
}