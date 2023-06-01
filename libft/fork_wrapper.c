/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:04:51 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/31 11:04:55 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	fork_wrapper(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		write(1, "fork error\n", 12);
		exit(1);
	}
	return (pid);
}
