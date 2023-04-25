/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:24:37 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/25 21:04:19 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* \033[12C moves cursor rigt 12 spots */
void	handle_signal(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
/* line 28 to 32, im disabeling ECHOCTL which means in not allowing the 
terminal to print ^C ^Z etc. But we will need them in cat  (which will be a child)*/
void	init_signals(void)
{
	struct sigaction	sa;
	struct termios		term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); //currently it completely disables ^c even when the program exits
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle_signal;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}