/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:20:16 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/01 13:58:45 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long int	ft_atol(const char *str)
{
	long int	sign;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' && str[1] >= '0' && str[1] <= '9')
		str++;
	else if (*str == '-' && str[1] >= '0' && str[1] <= '9')
	{
		str++;
		sign = -1;
	}
	if (*str >= '0' && *str <= '9')
		return (ft_tatoi(str, sign));
	return (0);
}

long int	ft_tatoi(const char *str, int sign)
{
	int			len;
	int			i;
	int			max;
	long int	numb;

	i = -1;
	len = 0;
	max = 0;
	numb = 0;
	while (str[len] >= '0' && str[len] <= '9')
		len++;
	max = len;
	while (++i < max)
		numb = numb + (str[i] - 48) * ft_pow10(--len);
	return (numb * sign);
}

long int	ft_pow10(int n)
{
	int	base;
	int	i;

	i = -1;
	base = 1;
	while (++i < n)
		base = base * 10;
	return (base);
}
