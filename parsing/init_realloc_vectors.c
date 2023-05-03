/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_realloc_vectors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:54:30 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/03 10:09:26 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_vec(t_argv_vec	*argv)
{
	argv->argv = (char **)malloc(5 * sizeof(char *));
	if(argv->argv == NULL)
		exit(1); ////// handle exit
	argv->curr = 0;
	argv->cap = 5;
}

void	init_token(t_token_vec	*tkn_vec)
{
	if (tkn_vec->token != 0)
		return ;
	tkn_vec->token = ft_calloc(11, sizeof(char));
	if (tkn_vec->token == NULL)
		exit(1); /////// handle exit
	tkn_vec->cap = 10;
	tkn_vec->curr = 0;
}

void	realloc_vector(t_argv_vec	*argv)
{
	char	**new_argv;
	int i;

	i = 0;
	argv->cap *= 2;
	new_argv = (char **)malloc(argv->cap * sizeof(char *));
	if(new_argv == NULL)
		exit(1); ////// handle exit
	while (i < argv->curr)
	{
		new_argv[i] = argv->argv[i];
		i++;
	}
	free(argv->argv);
	argv->argv = new_argv;
}

void	realloc_token(t_token_vec	*tkn_vec)
{
	char	*new_token;
	int i;

	i = 0;
	tkn_vec->cap *= 2;
	new_token = ft_calloc(tkn_vec->cap + 1, sizeof(char));
	if(new_token == NULL)
		exit(1); ////// handle exit
	ft_strlcpy(new_token, tkn_vec->token, tkn_vec->cap);
	free(tkn_vec->token);
	tkn_vec->token = new_token;
}

void	free_argv(t_argv_vec	*argv)
{
	int i;

	i = 0;
	while (i < argv->curr)
	{
		free(argv->argv[i]);
		i++;
	}
	free(argv->argv);
}