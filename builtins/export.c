/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:07:36 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/05 17:42:40 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_error_handling(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		printf("no str in export error handling\n");
		return (1);
	}		
	// if (ft_isdigit(str[0]) == 1)
	// {
	// 	printf("minishell: export: '%s': not a valid identifier\n", str);
	// 	return (1);
	// }
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 1 || str[i] == '_' || str[i] == '=')
			i++;
		else
		{
			printf("minishell: export: '%s': not a valid identifier\n", str);
			return (1);
		}	
	}
	return (0);
}

void	add_env(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->argv->curr)
	{
		if (export_error_handling(data->argv->argv[i]) == 1)
			data->exit_code = 1;
		else
		{
			ft_add_back(&data->envp_list, \
			data->argv->argv[i], data->num_of_env_var);
			data->num_of_env_var++;
		}
		i++;
	}
}

void	modify_existing_env(char *value, char *str)
{
	char *new_value;

	new_value = get_value(str);
	if (value != NULL)
	 	free(value);
	value = new_value;
	return ;	
}

int	check_existing_and_modify(t_data *data, char *str)
{
	t_envp_list *list;
	char		*key;
	int			len;

	list = data->envp_list;
	key = get_key(str);
	len = ft_strlen(key);
	if (!list)
	{
		printf("list copy error in checking existing env");
		return (1);
	}
	while (list)
	{
		if (ft_strncmp(key, list->key, len) == 0)
		{
			printf("value: %s\n", list->value);
			modify_existing_env(list->value, str);
			printf("value: %s\n", list->value);
			return (1);
		}
		list = list->next;
	}
	free(key);
	return (0);
}

void	export_var(t_data *data)
{
	int	i;

	i = 0;
	data->exit_code = 0;
	while (data->argv->argv[i])
		i++;
	if (i == 1)
	{
		export_without_args(data);
		return ;
	}
	i = 1;
	while (i < data->argv->curr)
	{
		if (check_existing_and_modify(data, data->argv->argv[i]) == 0)
			add_env(data);
		i++;
	}
	return ;
}
