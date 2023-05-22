/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_case_ins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:09:41 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/14 15:42:43 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_case_ins(const char *str1, const char *str2, size_t n)
{
	int	result;

	result = 0;
	while (n > 0 && result == 0)
	{
		result += ft_tolower(*(unsigned char *)str1) - \
		ft_tolower(*(unsigned char *)str2);
		if (*str1 == 0 || *str2 == 0)
			break ;
		n--;
		str1++;
		str2++;
	}
	if (result < 0)
		return (-1);
	else if (result > 0)
		return (1);
	else
		return (result);
}
