/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:21:59 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/17 14:58:28 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export_without_args(t_envp_list *list, int i, int flag)
{
	while (list)
	{
		i = 0;
		flag = 0;
		printf("declare -x ");
		while (list->variable[i] != '\0')
		{
			if (list->variable[i - 1] == '=')
			{
				flag++;
				printf("%c", '"');
			}
			printf("%c", list->variable[i]);
			i++;
		}
		if (flag > 0)
			printf("%c\n", '"');
		else
			printf("\n");
		list = list->next;
	}
	return ;
}

void	export_without_args(char **argv)
{
	t_envp_list	*list;
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	list = g_data.envp_list;
	if (!list)
		return ;
	print_export_without_args(list, i, flag);
	return ;
}

int	check_key_in_export(char *key, char *str)
{
	int	i;

	i = 0;
	while (key[i] != '\0')
	{
		if (ft_isalpha(key[i]) == 1 || key[i] == '_' \
		|| (ft_isdigit(key[i]) == 1 && i != 0))
			i++;
		else
		{
			printf("minishell: export: '%s': not a valid identifier\n", str);
			g_data.exit_code = 1;
			free(key);
			return (1);
		}
	}
	return (0);
}
