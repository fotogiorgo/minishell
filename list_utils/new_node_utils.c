/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:45:05 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/05 15:13:48 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*key_without_value(char *str)
{
	int		i;
	char	*key;

	i = ft_strlen(str);
	key = (char *) malloc (sizeof(char) * i + 1);
	i = 0;
	while (str[i])
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		key = (char *) malloc (sizeof(char) * i + 1);
		i = 0;
		while (str[i] != '=')
		{
			key[i] = str[i];
			i++;
		}
		key[i] = '\0';
		return (key);
	}
	else
	{
		key = key_without_value(str);
		return (key);
	}	
	return (NULL);
}

char	*put_value(char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i])
		i++;
	value = (char *) malloc (sizeof(char) * i + 1);
	i = 0;
	while (str[i])
	{
		value[i] = str[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	*get_value(char *str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		i++;
		value = put_value(&str[i]);
		return (value);
	}
	return (NULL);
}
