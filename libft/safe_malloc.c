/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:09:35 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/01 19:10:34 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	free_everything(t_list **root)
{
	if ((*root)->next)
		free_everything(&((*root)->next));
	if ((*root)->content != NULL)
	{
		printf("freeing: %p\n", (*root)->content);
		free((*root)->content);
	}
	free(*root);
}	

// if you call this function with 0 it detroys everything
// this function is under contruction DO NOT USE
// 
void	*safe_malloc(size_t size)
{
	static t_list	*root;
	t_list			*new_node;
	void			*ret;

	if (size == 0)
	{
		free_everything(&root);
		exit(1);
	}
	ret = malloc(size);
	printf("allocated: %p\n", ret);
	if (ret == NULL)
	{
		free_everything(&root);
		return (0);
	}
	new_node = ft_lstnew(ret);
	ft_lstadd_back(&root, new_node);
	return (ret);
}
