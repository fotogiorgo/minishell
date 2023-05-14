/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:07:36 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/14 12:48:38 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_key_in_export(char *key, char *str)
{
	int	i;

	i = 0;
	while (key[i] != '\0')
	{
		if (ft_isalpha(key[i]) == 1 || key[i] == '_' || (ft_isdigit(key[i]) == 1 && i != 0))
			i++;
		else
		{
			printf("minishell: export: '%s': not a valid identifier\n", str);
			data.exit_code = 1;
			free(key);
			return (1);
		}
	}
	return (0);
}

int	export_error_handling(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (!str)
	{
		printf("no str in export error handling\n");
		return (1);
	}
	key = get_key(str);
	if (!key || *key == '\0')
	{
		printf("minishell: export: '%s': not a valid identifier\n", str);
		data.exit_code = 1;
		return (1);
	}
	if (check_key_in_export(key, str) == 1)
		return (1);
	else
		free(key);
	return (0);
}

void	add_env(char *argv)
{
	if (export_error_handling(argv) == 1)
		data.exit_code = 1;
	else
	{
		ft_add_back(&data.envp_list, \
		argv, data.num_of_env_var);
		data.num_of_env_var++;
	}
}

char	*modify_existing_env(t_envp_list *list, char *str)
{
	char *new_value;

	new_value = get_value(str);
	free(list->variable);
	list->variable = ft_strdup(str);
	if (list->value != NULL)
	 	free(list->value);
	return (new_value);	
}

int	check_existing_and_modify(char *str, t_envp_list **lst)
{
	t_envp_list *list;
	char		*key;
	int			len;

	list = *lst;
	key = get_key(str);
	len = ft_strlen(key);
	if (!list)
	{
		printf("list copy error in checking existing env");
		return (1);
	}
	while (list)
	{
		if (ft_strncmp(key, list->key, (len + 1)) == 0)
		{
			list->value = modify_existing_env(list, str);
			free(key);
			return (1);
		}
		list = list->next;
	}
	free(key);
	return (0);
}

void	export_var(char **argv)
{
	int	i;

	data.exit_code = 0;
	if (argv[0] == NULL)
	{
		export_without_args(argv);
		return ;
	}
	i = 0;
	while (argv[i] != NULL)
	{
		if (check_existing_and_modify(argv[i], &data.envp_list) == 0)
			add_env(argv[i]);
		i++;
	}
	return ;
}
