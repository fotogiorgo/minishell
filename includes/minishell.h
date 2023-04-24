/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:25:28 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/24 14:44:26 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h> //readline
# include <readline/history.h> //add history

#define MAXIN 1024 // maxinput

void get_pwd(void);
void	check_command_from_input(char *input);

#endif