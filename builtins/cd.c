/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:14:12 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/09 12:42:48 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_home(void)
{
	t_envp_list *list;

	list = data.envp_list;
	while (list)
	{
		if (ft_strncmp(list->key, "HOME", 5) == 0)
			break;
		else
			list = list->next;
	}
	if (list == NULL)
	{
		printf("minishell: cd: HOME not set");
		data.exit_code = 1;
		return ;
	}
	else
	{
		if (chdir(list->value))
		{
			printf("bash: cd: %s: No such file or directory\n", list->value);
			data.exit_code = 1;
			return ;
		}
	}
}

void	get_cd(char **argv)
{
	data.exit_code = 0;
	if (data.argv->curr - 1 == 0)
	{
		cd_home();
		return ;
	}
	if (argv[0][0] == '\0')
		return ;
	if (chdir(argv[0]) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", argv[0]);
		data.exit_code = 1;
		return ;
	}
	return ;
}