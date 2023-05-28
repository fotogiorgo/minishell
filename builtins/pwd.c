/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:28:12 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/28 18:33:01 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_pwd(void)
{
	char	cwd[1024];

	g_data.exit_code = 0;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return ;
}
