/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:41:25 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/11 15:21:48 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	**realloc_two_d(void **array, int curr_size)
{
	void	**new_array;

	new_array = malloc(curr_size * 2 * sizeof(void *));
	if (new_array == NULL)
		return (NULL);
	curr_size--;
	while (curr_size >= 0)
	{
		new_array[curr_size] = array[curr_size];
		curr_size--;
	}
	free(array);
	return(new_array);
}