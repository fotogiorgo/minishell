/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_int_only.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:43:54 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/01 19:18:56 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static int	positive_num(char *str, int *fail_switch)
{
	int			result;

	result = 0;
	while (48 <= *str && *str <= 57)
	{
		result *= 10;
		result += *str - 48;
		str++;
		if (result < 0)
		{
			*fail_switch = 1;
			return (0);
		}
	}
	if (*str != 0)
	{
		*fail_switch = 1;
		return (0);
	}
	return (result);
}

static int	negative_num(char *str, int *fail_switch)
{
	int			result;

	result = 0;
	while (48 <= *str && *str <= 57)
	{
		result *= 10;
		result -= *str - 48;
		str++;
		if (result > 0)
		{
			*fail_switch = 1;
			return (0);
		}
	}
	if (*str != 0)
	{
		*fail_switch = 1;
		return (0);
	}
	return (result);
}

int	atoi_int_only(const char *str, int *fail_switch)
{
	*fail_switch = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' \
			|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		str++;
		if (*str == 0)
		{
			*fail_switch = 1;
			return (0);
		}
		return (negative_num((char *)str, fail_switch));
	}
	else if (*str == '+')
	{
		str++;
		if (*str == 0)
		{
			*fail_switch = 1;
			return (0);
		}
	}
	return (positive_num((char *)str, fail_switch));
}
