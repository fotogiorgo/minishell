/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:28:12 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/26 11:28:49 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void get_pwd(char *str)
{
	char	cwd[1024];
	int		i;

	i = 3;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			printf("minishell: usage: pwd with no options\n");
			return ;
		}
		i++;
	}
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}