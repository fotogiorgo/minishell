/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:33:18 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/26 12:33:52 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*return_wrong_input(char *input)
{
	int	i;
	char *wrong_input_str;

	i = 0;

	while (input[i] != ' ' && input[i] != '\0')
		i++;
	wrong_input_str = (char *) malloc (sizeof(char) * i + 1);
	i = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		wrong_input_str[i] = input[i];
		i++;
	}
	free(input);
	return (wrong_input_str);
}

void	check_command_from_input(char *input)
{
	char	*str;
	char	*wrong_str;

	str = remove_quotes(input);
	if (ft_strncmp_case_ins(str, "pwd", 3) == 0)
		get_pwd(str);
	else if (ft_strncmp_case_ins(str, "echo", 4) == 0)
		get_echo(str);
	else if (ft_strncmp_case_ins(input, "cd", 2) == 0)
		get_pwd(str);
	else if (ft_strncmp_case_ins(input, "export", 6) == 0)
		get_pwd(str);
	else if (ft_strncmp_case_ins(input, "unset", 5) == 0)
		get_pwd(str);
	else if (ft_strncmp_case_ins(input, "env", 3) == 0)
		get_pwd(str);
	else if (ft_strncmp_case_ins(input, "exit", 3) == 0)
		exit_func();
	else
	{
		wrong_str = return_wrong_input(str);
		printf("minishell: %s: command not found\n", wrong_str);
		free(wrong_str);
	}
	return ;
}