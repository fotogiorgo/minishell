/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:47:45 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/17 14:06:46 by kakumar          ###   ########.fr       */
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
		return (NULL);
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
	if (*str[0] == ' ' || *str[0] == '\0' || *str[0] == '?' || *str[0] == '\'' || *str[0] == '\"' )
	{
		do_edges(str[0], tkn_vec);
		if (*str[0] == '?')
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
