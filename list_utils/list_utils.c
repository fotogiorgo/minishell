/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:17:31 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/14 15:43:45 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envp_list	*ft_newlst(char	*str, int i)
{
	t_envp_list	*l;

	l = malloc(sizeof(t_envp_list));
	if (!l)
		return (0);
	l->index = i;
	l->variable = ft_strdup(str);
	l->key = get_key(str);
	l->value = get_value(str);
	l->next = NULL;
	return (l);
}

void	ft_add_back(t_envp_list **lst, char *str, int i)
{
	t_envp_list	*new_node;
	t_envp_list	*current;

	new_node = ft_newlst(str, i);
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		current = *lst;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

char	*get_value_from_key(char *key)
{
	t_envp_list	*list;
	char		*result;
	int			len;

	len = ft_strlen(key);
	list = g_data.envp_list;
	while (list)
	{
		if (ft_strncmp(list->key, key, len + 1) == 0)
		{
			result = list->value;
			return (result);
		}
		list = list->next;
	}
	return (NULL);
}
