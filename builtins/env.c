/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:52:39 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/17 14:57:59 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_all_env(void)
{
	t_envp_list	*list_copy;

	g_data.exit_code = 0;
	list_copy = g_data.envp_list;
	while (list_copy)
	{
		if (ft_strchr(list_copy->variable, '=') != 0)
			printf("%s\n", list_copy->variable);
		list_copy = list_copy->next;
	}
	return ;
}

t_envp_list	*create_our_envp(char **envp)
{
	int			i;
	t_envp_list	*envp_list;

	i = 0;
	envp_list = ft_newlst(envp[i], g_data.num_of_env_var);
	if (envp_list == NULL)
		return (NULL);
	g_data.num_of_env_var++;
	while (envp[g_data.num_of_env_var] != NULL)
	{
		ft_add_back(&envp_list, envp[g_data.num_of_env_var], g_data.num_of_env_var);
		g_data.num_of_env_var++;
	}
	return (envp_list);
}
