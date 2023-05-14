/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:50:03 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/10 11:36:14 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_quote(char	**str, t_token_vec	*tkn_vec, char quote)
{
	static int	searching_quote = 0;
	static char	which_quote;

	if (searching_quote == 1)
		quote = which_quote;
	str[0]++; 
	while(*str[0] != quote && *str[0] != '\0')
	{
		if (*str[0] == '$' && quote != '\'')
			add_env_var(str, tkn_vec);
		else
			add_char_to_token(str, tkn_vec);
	}
	if (*str[0] == '\0')
	{
		add_nl_to_token(tkn_vec);
		searching_quote = 1;
		which_quote = quote;
		return (0);
	}
	else
	{
		searching_quote = 0;
		str[0]++;
		return(1);
	}
}

static int	get_token(char	**str, char **token)
{
	static t_token_vec	tkn_vec;

	init_token(&tkn_vec);
	while(*str[0] != '\0' && *str[0] != ' ')
	{
		if (*str[0] == '\'' || *str[0] == '\"')
		{
			if(!find_quote(str, &tkn_vec, *str[0]))
				return (1);
		}
		else if(*str[0] == '$')
			add_env_var(str, &tkn_vec);
//		else if pipe / redirection
		else
			add_char_to_token(str, &tkn_vec);
	}
	*token = tkn_vec.token;
	tkn_vec.token = 0;
	if(*str[0] == '\0')
		return (0);
	else
		return (1);
}
// if  we have an input which ends with a space it will give us a null ending 2d array
// actually the character will be nul.. not the pointer
static int	split_argv(char *str, t_argv_vec	*argv)
{
	while (get_token(&str, &argv->argv[argv->curr]))
	{
		if(*str == '\0')
			return (0); // this means opened quote was given and we need more input
		else
			argv->curr++;
		if (argv->curr == argv->cap)
			realloc_vector(argv);
		str++;
	}
	argv->curr++;
	return (1);
}

void	print_argv(t_argv_vec	argv)
{
	for(int i = 0; i < argv.curr; i++)
	{
		printf("token %i: %s\n", i, argv.argv[i]);
		// printf("token adress %i: %p\n", i, argv.argv[i]);
		// printf("printing - curr: %i\n", argv.curr);
	}
}
/* if you do ctr-c while waiting for a quote, its focked (well, not really, it just doesnt work like bash) */
int	tokenize_input(char *str, t_argv_vec	*argv)
{
	char	*dummy;

	init_vec(argv);
	while (!split_argv(str, argv))
	{
		free(str);
		rl_on_new_line();
		str = readline("> ");
		if (str == NULL)
		{
			free_argv(argv);
			write(1, "\033[1A\033[3C", 9);
			write(1, "minishell: unexpected EOF while looking for matching `\"\'\n", 58);
			write(1, "minishell: syntax error: unexpected end of file\n", 49);
			return (0);
		}
		dummy = ft_calloc(sizeof(char), ft_strlen(str) + 2);
		*dummy = '\"';
		ft_strlcat(dummy, str, ft_strlen(str) + 2);
		free(str);
		str = dummy;
	}
	// print_argv(*argv);
	free(str);
	return (1);
}
