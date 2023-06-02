/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:58:05 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/02 09:17:26 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_char_to_token(char	**str, t_token_vec	*tkn_vec)
{
	if (tkn_vec->curr == tkn_vec->cap)
		realloc_token(tkn_vec);
	tkn_vec->token[tkn_vec->curr] = *str[0];
	str[0]++;
	tkn_vec->curr++;
}

void	add_nl_to_token(t_token_vec	*tkn_vec)
{
	if (tkn_vec->curr == tkn_vec->cap)
		realloc_token(tkn_vec);
	tkn_vec->token[tkn_vec->curr] = '\n';
	tkn_vec->curr++;
}

int	add_operator(char **str, t_argv_vec *argv)
{
	static t_token_vec	tkn_vec;

	init_token(&tkn_vec);
	add_char_to_token(str, &tkn_vec);
	if (*str[0] == '>' || *str[0] == '<')
		add_char_to_token(str, &tkn_vec);
	if (*str[0] == '|' || *str[0] == '<' || *str[0] == '>' || *str[0] == '\0')
	{
		printf("minishell: syntax error near \
		unexpected token `%s'\n", tkn_vec.token);
		argv->argv[argv->curr] = tkn_vec.token;
		argv->curr++;
		tkn_vec.token = 0;
		return (0);
	}
	else
	{
		tkn_vec.token[ft_strlen(tkn_vec.token) + 1] = 'o';
		argv->argv[argv->curr] = tkn_vec.token;
		tkn_vec.token = 0;
	}
	return (1);
}

int	deal_with_operators(char **str, t_argv_vec *argv)
{
	if (!add_operator(str, argv))
		return (0);
	else
		argv->curr++;
	if (argv->curr == argv->cap)
		realloc_vector(argv);
	if (*str == '\0')
	{
		printf("minishell: Unclosed quotes\n");
		return (0);
	}
	return (1);
}
