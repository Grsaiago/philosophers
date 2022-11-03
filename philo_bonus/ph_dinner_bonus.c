/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dinner_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:46:45 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 19:40:10 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	dine(t_control *control)
{
	death_refresh(control);
	while (42)
	{
		control->timestamp = get_time(&control->tv_timestamp, 1000);
		sem_wait(control->stout_sem);
		printf("%ld %d is thinking\n", control->timestamp, control->phid);
		sem_post(control->stout_sem);
		dine_take_forks(control); /*take forks*/
		dine_eat(control); /*eat routine*/
		control->timestamp = get_time(&control->tv_timestamp, 1000);
		sem_wait(control->stout_sem);
		printf("%ld %d is sleeping\n", control->timestamp, control->phid);
		sem_post(control->stout_sem);
		usleep(control->time_to_sleep);
	}
	return ;
}

void	dine_take_forks(t_control *control)
{
		sem_wait(control->forks);
		control->timestamp = get_time(&control->tv_timestamp, 1000);
		sem_wait(control->stout_sem);
		printf("%ld %d has taken a fork\n",control->timestamp, control->phid);
		sem_post(control->stout_sem);
		sem_wait(control->forks);
		control->timestamp = get_time(&control->tv_timestamp, 1000);
		sem_wait(control->stout_sem);
		printf("%ld %d has taken a fork\n",control->timestamp, control->phid);
		sem_post(control->stout_sem);
		return ;
}

void	dine_eat(t_control *control)
{
		death_refresh(control);
		control->timestamp = get_time(&control->tv_timestamp, 1000);
		sem_wait(control->stout_sem);
		printf("%ld %d is eating\n", control->timestamp, control->phid);
		sem_post(control->stout_sem);
		usleep(control->time_to_eat);
		sem_post(control->forks);
		sem_post(control->forks);
		return ;
}
