/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:35:05 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/15 17:52:12 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	else
		return (0);
}

int	if_number(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac < 4)
		return (1);
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!ph_isdigit(av[i][j]))
			{
				printf("Error!\nNon Number/negative input\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	if_in_range(int ac, char **av)
{
	long int	numb;
	int			i;

	i = 1;
	while (i < ac)
	{
		numb = ft_atol(av[i]);
		if (numb > INT_MAX || numb <= 0)
		{
			printf("Error!\nNumber larger than INT_MAX or 0\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_args(int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
	{
		printf("Error!\nNot enough/Too mmany args\n");
		return (1);
	}
	if (if_number(ac, av))
		return (1);
	if (if_in_range(ac, av))
		return (1);
	return (0);
}
