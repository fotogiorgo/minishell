/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:47:45 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/28 18:32:43 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_from_list(char *var_name)
{
	t_envp_list	*list;
	int			len;
	char		*ret;

	list = g_data.envp_list;
	len = ft_strlen(var_name) + 1;
	while (list && *var_name != '\0')
	{
		if (ft_strncmp(list->key, var_name, len) == 0)
			break ;
		list = list->next;
	}
	if (list == NULL)
	{
		if (*g_data.argv->argv[g_data.argv->curr-1] == '>' || ft_strncmp(g_data.argv->argv[g_data.argv->curr-1], "<", 2) == 0)
		{
			printf("minishell: $%s: ambiguous redirect\n", var_name);
			ret = ft_strjoin("$", var_name);
			return (ret);
		}
		else if (ft_strncmp(g_data.argv->argv[g_data.argv->curr-1], "<<", 2) == 0)
		{
			ret = ft_strjoin("$", var_name);
			return (ret);
		}
		return (NULL);
	}
	else if (ft_strncmp(g_data.argv->argv[g_data.argv->curr-1], "<<", 2) == 0)
	{
		ret = ft_strjoin("$", var_name);
		return (ret);
	}
	else
		ret = list->value;
	return (ret);
}

void	do_edges(char *str, t_token_vec *tkn_vec)
{
	char	*var_value;
	char	*exit_code;

	if (*str == ' ' || *str == '\0')
	{
		var_value = ft_strdup("$");
		while (*var_value)
			add_char_to_token(&var_value, tkn_vec);
		return ;
	}
	else if (*str == '?')
	{
		exit_code = ft_itoa(g_data.exit_code);
		str++;
		while (*exit_code)
			add_char_to_token(&exit_code, tkn_vec);
		return ;
	}
	else if (ft_isdigit(*str) == 1)
		return ;
	else if (ft_isalpha(*str) == 0)
	{
		var_value = ft_strdup("$");
		while (*var_value)
			add_char_to_token(&var_value, tkn_vec);
	}
	return ;
}

void	add_env_var(char **str, t_token_vec *tkn_vec)
{
	char	var_name[32767];
	char	*var_value;
	int		i;
	char	*exit_code;

	i = 0;
	str[0]++;
	if (*str[0] == ' ' || *str[0] == '\0' || ft_isdigit(*str[0]) == 1  || *str[0] == '_' || ft_isalpha(*str[0]) == 0)
	{
		do_edges(str[0], tkn_vec);
		if (*str[0] == '?' || ft_isdigit(*str[0]) == 1)
			str[0]++;
		return ;
	}
	while (ft_isalpha(*str[0]))
	{
		var_name[i] = *str[0];
		i++;
		str[0]++;
	}
	var_name[i] = 0;
	var_value = get_env_from_list(var_name);
	if (var_value == NULL)
		return ;
	while (*var_value)
		add_char_to_token(&var_value, tkn_vec);
}
