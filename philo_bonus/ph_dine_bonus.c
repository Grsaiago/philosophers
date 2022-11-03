/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:46:45 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 17:58:44 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	dine(t_control *control)
{
	death_refresh(control);
	while (42)
	{
		sem_wait(control->stout_sem);
		control->timestamp = get_time(&control->tv_timestamp, 100);
		printf("%ld %d is thinking\n", control->timestamp, control->phid);
		sem_post(control->stout_sem);
		dine_take_forks(control); /*take forks*/
		dine_eat(control); /*eat routine*/
		sem_wait(control->stout_sem);
		control->timestamp = get_time(&control->tv_timestamp, 100);
		printf("%ld %d is sleeping\n", control->timestamp, control->phid);
		sem_post(control->stout_sem);
		usleep(control->time_to_sleep);
	}
	return ;
}

void	dine_take_forks(t_control *control)
{
		sem_wait(control->forks);
		sem_wait(control->stout_sem);
		control->timestamp = get_time(&control->tv_timestamp, 100);
		printf("%ld %d has taken a fork\n",control->timestamp, control->phid);
		sem_post(control->stout_sem);
		sem_wait(control->forks);
		sem_wait(control->stout_sem);
		control->timestamp = get_time(&control->tv_timestamp, 100);
		printf("%ld %d has taken a fork\n",control->timestamp, control->phid);
		sem_post(control->stout_sem);
		return ;
}

void	dine_eat(t_control *control)
{
		death_refresh(control);
		sem_wait(control->stout_sem);
		control->timestamp = get_time(&control->tv_timestamp, 100);
		printf("%ld %d is eating\n", control->timestamp, control->phid);
		sem_post(control->stout_sem);
		usleep(control->time_to_eat);
		sem_post(control->forks);
		sem_post(control->forks);
		return ;
}
