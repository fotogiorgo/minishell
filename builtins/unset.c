/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:51:25 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/31 14:32:57 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_node(t_envp_list *temp, t_envp_list *prev, int len, char *str)
{
	if (temp == NULL && ft_strncmp(str, temp->key, len) == 0)
	{
		free(prev->variable);
		free(prev->key);
		free(prev->value);
		free(prev);
		prev = NULL;
	}
	else if (temp != NULL && ft_strncmp(str, temp->key, len) == 0)
	{
		if (temp->index == 0)
			prev = temp->next;
		else
			prev->next = temp->next;
		free(temp->value);
		free(temp->key);
		free(temp->variable);
		free(temp);
	}
	else
		return ;
}

int	error_handle_unset(char *str)
{
	int	i;

	i = 0;
	if (!str || *str == '\0')
	{
		printf("minishell: unset: '': not a valid identifier\n");
		g_data.exit_code = 1;
		return (1);
	}
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1 || str[i] == '_' \
		|| (ft_isdigit(str[i]) == 1 && i != 0))
			i++;
		else
		{
			printf("minishell: unset: '%s': not a valid identifier\n", str);
			g_data.exit_code = 1;
			return (1);
		}
	}
	return (0);
}

void	unset_node(t_envp_list *temp, t_envp_list *prev, char *argv, int len)
{
	int	i;

	i = 0;
	while (temp != NULL && ft_strncmp(argv, temp->key, len) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL && ft_strncmp(argv, prev->key, len) != 0)
		i++;
	else
	{
		delete_node(temp, prev, len, argv);
		i++;
	}
}

void	unset_var(char **argv)
{
	t_envp_list	*temp;
	t_envp_list	*prev;
	int			i;
	int			len;

	i = 0;
	g_data.exit_code = 0;
	while (argv[i] != NULL)
	{
		len = ft_strlen(argv[i]) + 1;
		temp = g_data.envp_list;
		if (error_handle_unset(argv[i]) == 0)
		{
			unset_node(temp, prev, argv[i], len);
			i++;
		}
		else
			i++;
	}
	return ;
}
