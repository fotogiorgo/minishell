/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:58:05 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/02 17:58:23 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_char_to_token(char	**str, t_token_vec	*tkn_vec)
{
	if(tkn_vec->curr == tkn_vec->cap)
		realloc_token(tkn_vec);
	tkn_vec->token[tkn_vec->curr] = *str[0];
	str[0]++;
	tkn_vec->curr++;
}

void	add_nl_to_token(t_token_vec	*tkn_vec)
{
	if(tkn_vec->curr == tkn_vec->cap)
		realloc_token(tkn_vec);
	tkn_vec->token[tkn_vec->curr] = '\n';
	tkn_vec->curr++;
}