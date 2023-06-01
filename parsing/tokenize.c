/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:50:03 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/01 11:23:13 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_quote(char **str, t_token_vec	*tkn_vec, char quote)
{
	str[0]++;
	while (*str[0] != quote && *str[0] != '\0')
	{
		if (*str[0] == '$' && quote != '\'')
			add_env_var(str, tkn_vec);
		else
			add_char_to_token(str, tkn_vec);
	}
	if (*str[0] == '\0')
	{
		return (0);
	}
	else
	{
		str[0]++;
		if (ft_strlen(tkn_vec->token) == 0)
			g_data.argv->curr++;
		return (1);
	}
}

static int	get_token(char **str, char **token)
{
	static t_token_vec	tkn_vec;

	while (*str[0] == ' ')
		str[0]++;
	if (*str[0] == '\0')
		return (2);
	init_token(&tkn_vec);
	while (*str[0] != '\0' && *str[0] != ' ')
	{
		if (*str[0] == '\'' || *str[0] == '\"')
		{
			if (!find_quote(str, &tkn_vec, *str[0]))
			{
				// free(tkn_vec.token);
				return (1);
			}
		}
		else if (*str[0] == '$')
			add_env_var(str, &tkn_vec);
		else if (*str[0] == '|' || *str[0] == '<' || *str[0] == '>')
		{
			if (ft_strlen(tkn_vec.token) == 0)
			{
				free(tkn_vec.token);
				break ;
			}
			break ;
		}
		else
			add_char_to_token(str, &tkn_vec);
	}
	*token = tkn_vec.token;
	// printf("token: %s\n", tkn_vec.token);
	tkn_vec.token = 0;
	while (*str[0] == ' ' && *str[0] != '\0')
		str[0]++;
	if (*str[0] == '\0')
		return (0);
	else
		return (1);
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
		// printf("token: %s || tkn adr: %p\n", tkn_vec.token, tkn_vec.token);
		printf("minishell: syntax error near unexpected token `%s'\n", tkn_vec.token);
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

// int	deal_with_operators(char **str, t_argv_vec *argv)
// {
// 	if (!add_operator(str, argv))
// 		return (0);
// 	else
// 		argv->curr++;
// 	if (argv->curr == argv->cap)
// 		realloc_vector(argv);
// 	if (*str == '\0')
// 	{
// 		printf("minishell: Unclosed quotes\n");
// 		free_argv(argv);
// 		return (0);
// 	}
// 	return (1);
// }

static int	split_argv(char *str, t_argv_vec *argv)
{
	int i;

	i = get_token(&str, &argv->argv[argv->curr]);
	while (i == 1)
	{
		if (*str == '\0')
		{
			printf("minishell: Unclosed quotes\n");
			// free_argv(argv);
			return (0);
		}
		else if (argv->argv[argv->curr] && argv->argv[argv->curr][0] != '\0')
			argv->curr++;
		if (argv->curr == argv->cap)
			realloc_vector(argv);
		if (*str == '|' || *str == '<' || *str == '>')
		{
			// if (deal_with_operators(str, argv) == 0)
			// 	return (0);
			if (!add_operator(&str, argv))
			{
				// free_argv(argv);
				return (0);
			}
			else
				argv->curr++;
			if (argv->curr == argv->cap)
				realloc_vector(argv);
			if (*str == '\0')
			{
				printf("minishell: Unclosed quotes\n");
				// free_argv(argv);
				return (0);
			}
		}
		i = get_token(&str, &argv->argv[argv->curr]);
	}
	if (i == 2)
	{
		// free_argv(argv);
		return (0);
	}
	argv->curr++;
	return (1);
}

void	print_argv(t_argv_vec argv)
{
	for (int i = 0; argv.argv[i] != NULL; i++)
	{
		printf("token %i: %s\n", i, argv.argv[i]);
		printf("token adress %i: %p\n", i, argv.argv[i]);
	}
}

int	tokenize_input(char *str, t_argv_vec *argv)
{
	init_vec(argv);
	if (split_argv(str, argv) == 0)
	{
		// print_argv(*argv);
		free(str);
		return (0);
	}
	else
		free(str);
	// print_argv(*argv);
	return (1);
}
