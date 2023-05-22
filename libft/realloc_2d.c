/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:41:25 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/15 15:47:10 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	**realloc_two_d(void **array, int curr_size)
{
	void	**new_array;

	new_array = ft_calloc(curr_size * 2, sizeof(void *));
	if (new_array == NULL)
		return (NULL);
	curr_size--;
	while (curr_size >= 0)
	{
		new_array[curr_size] = array[curr_size];
		curr_size--;
	}
	free(array);
	return (new_array);
}
