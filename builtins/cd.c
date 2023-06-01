/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:14:12 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/31 11:00:56 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_home(void)
{
	t_envp_list	*list;

	list = g_data.envp_list;
	while (list)
	{
		if (ft_strncmp(list->key, "HOME", 5) == 0)
			break ;
		else
			list = list->next;
	}
	if (list == NULL)
	{
		printf("minishell: cd: HOME not set");
		g_data.exit_code = 1;
		return ;
	}
	else
	{
		if (chdir(list->value))
		{
			printf("minishell: cd: %s: No such file or directory\n", \
			list->value);
			g_data.exit_code = 1;
		}
	}
}

void	change_oldpwd_env(char old[1024])
{
	t_envp_list	*list;
	char		*new_var;
	char		*new_value;

	list = g_data.envp_list;
	new_value = ft_strdup(old);
	while (list)
	{
		if (ft_strncmp(list->key, "OLDPWD", 7) == 0)
		{
			if (list->value != NULL)
				free(list->value);
			list->value = new_value;
			new_var = ft_strjoin("OLDPWD=", new_value);
			free(list->variable);
			list->variable = new_var;
			break ;
		}
		list = list->next;
	}
	return ;
}

void	change_pwd_env(char old[1024])
{
	t_envp_list	*list;
	char		*new_var;
	char		*new_value;
	char		curr_folder[1024];

	list = g_data.envp_list;
	getcwd(curr_folder, sizeof(curr_folder));
	new_value = ft_strdup(curr_folder);
	while (list)
	{
		if (ft_strncmp(list->key, "PWD", 4) == 0)
		{
			if (list->value != NULL)
				free(list->value);
			list->value = new_value;
			new_var = ft_strjoin("PWD=", new_value);
			free(list->variable);
			list->variable = new_var;
			break ;
		}
		list = list->next;
	}
	change_oldpwd_env(old);
	return ;
}

void	get_cd(char **argv)
{
	char	current_folder[1024];

	g_data.exit_code = 0;
	getcwd(current_folder, sizeof(current_folder));
	if (argv[0] == NULL)
	{
		cd_home();
		change_pwd_env(current_folder);
		return ;
	}
	if (argv[0][0] == '\0')
		return ;
	if (chdir(argv[0]) != 0)
	{
		if (errno == EACCES)
			printf("minishell: cd: %s: Permission denied\n", argv[0]);
		else if (errno == ENOENT)
			printf("minishell: cd: %s: No such file or directory\n", argv[0]);
		g_data.exit_code = 1;
		return ;
	}
	change_pwd_env(current_folder);
	return ;
}
