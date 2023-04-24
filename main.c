/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:21:19 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/24 14:44:08 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void init_shell(void)
{
	printf("\n\n\n\n Minishell by jofoto and kakumar \n\n\n\n");
}

int	take_input(char *str)
{
	char	*buff;
	int		len;
	
	len = ft_strlen(buff);
	buff = readline("minishell$ ");
	if (len != 0)
	{
		add_history(buff);
		ft_strlcpy(str, buff, len);
		return (0);
	}
	else
		return (1);
}

int main(void)
{
	char input_str[MAXIN];
	
	init_shell();
	while (1)
	{
		if (take_input(input_str))
			continue;
		check_command_from_input(input_str);
	}
}