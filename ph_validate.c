/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:35:05 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 16:36:18 by gsaiago          ###   ########.fr       */
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

void if_number(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac < 4)
		exit(1);
//	if (ac == 5)
//		incrementar o eat_count;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!ph_isdigit(av[i][j]))
			{
				printf("Error!");
				exit(1); // exit func
			}
			j++;
		}
		i++;
	}
	return ;
}

void validate_args(int ac, char **av)
{
	if_number(ac, av);
	

}
