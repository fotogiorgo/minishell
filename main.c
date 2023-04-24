/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:21:19 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/24 14:11:51 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_shell(void)
{
	printf("\n\n\n\n Minishell by jofoto and kakumar \n\n\n\n");
}

void get_pwd(void)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("Current dir: %s\n", cwd);
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
	char inputstr[100000];
	
	init_shell();
	while (1)
	{
		get_pwd();
		if (take_input(inputstr))
			continue;
	}
}