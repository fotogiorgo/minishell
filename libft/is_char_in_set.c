/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_char_in_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:06:25 by jofoto            #+#    #+#             */
/*   Updated: 2022/11/26 17:42:14 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_char_in_set(char c, char *set)
{
	while (*set != 0)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}