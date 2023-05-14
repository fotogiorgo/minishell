/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:54:57 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/10 16:59:42 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	fork_wrapper(void)
{
	int	pid;

	pid = fork();
	if(pid == -1)
	{
		write(1, "fork error\n", 12);
		exit(1);
	}
	return (pid);
}