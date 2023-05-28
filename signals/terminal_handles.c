/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_handles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:42:09 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/28 18:32:46 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*here, im disabeling ECHOCTL which means in not allowing the 
terminal to print ^C ^Z etc. But we will need them in cat (which will be a child)*/
void	disable_enable_echoctl(int enable)
{
	struct termios		term;

	if (enable == 0)
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	}
	else
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	}
}

void	init_terminal(void)
{
	disable_enable_echoctl(0);
}