/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:46:10 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/19 17:54:24 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_thread_struct(t_control *control, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
			exit (1);
	philo->nph = control->nph;
	philo->forkv = control->forkv;
	philo->mementomori = control->mementomori;
	philo->time_to_die = 100000;
	philo->time_to_eat = 200;
	philo->time_to_sleep = 200;
	philo->phid = i;
	philo->prev_f = i - 1;
	philo->next_f = i;
	if (philo->next_f >= control->nph)
			philo->next_f = philo->next_f % control->nph;
	return(philo);
}

void	*thread_execute(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	printf("Thread %d criada\n", philo->phid); //debug
	death_refresh(philo);
//	printf("valor de death_refresh do philo %d> |%ld|\n", philo->phid, philo->mementomori[philo->phid - 1]); //death_refresh first value
	while(42)
	{
		if (philo->phid == philo->nph)
		{
			pthread_mutex_lock(&philo->forkv[philo->prev_f]);
			printf("%d has taken a fork\n", philo->phid);
			pthread_mutex_lock(&philo->forkv[philo->next_f]);
		}
		else 
		{
			pthread_mutex_lock(&philo->forkv[philo->next_f]);
			printf("%d has taken a fork\n", philo->phid);
			pthread_mutex_lock(&philo->forkv[philo->prev_f]);
		}
		printf("%d is eating\n", philo->phid);
		usleep(philo->time_to_eat);
		death_refresh(philo);
		if (philo->phid == philo->nph)
		{
			pthread_mutex_unlock(&philo->forkv[philo->prev_f]);
			pthread_mutex_unlock(&philo->forkv[philo->next_f]);
		}
		else 
		{
			pthread_mutex_unlock(&philo->forkv[philo->next_f]);
			pthread_mutex_unlock(&philo->forkv[philo->prev_f]);
		}
		printf("%d is thinking\n", philo->phid);
		usleep(500);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int					i;
	t_control			*control;
	pthread_mutex_t		mutex;

	i = 0;
//	Na real, aquilo que eu estava pensando de criar um struct de controle e passar ele pra thread pra ela usar pra criar as coisas
//	vai dar problema, pq vai dar data racing no index por exemplo.
//	Eu tenho que criar uma função que vai criar cada struct dentro do while da main, popular e indexar ele num array de structs t_philo.
//	Dessa forma eu passo cada struct pra sua thread por index.
//	O struct control ainda pode ser usado como parâmetro pra create_thread_struct em...
	control = &(t_control){0}; // main control struct with info
	control->nph = atoi(argv[1]); // the number of philosophers
	control->mementomori = (long unsigned int *)ph_calloc(sizeof(long unsigned int), (control->nph + 1));
	control->thv = (pthread_t *)ph_calloc(sizeof(pthread_t *), (control->nph + 1)); // array in which every position will be a thread id
	control->philov = (t_philo **)ph_calloc(sizeof(t_philo *), (control->nph + 1)); // creating a vector with the address of every philo struct
	control->forkv= (pthread_mutex_t *)ph_calloc(sizeof(pthread_mutex_t), (control->nph + 1)); //create mutex vector to control everything, alongside the forkv
	control->time_to_die = 1000000;
	pthread_create(&control->vulture, NULL, &vulture, control);
	usleep(100);
	while (i < control->nph) // initialize mutexes
	{
		pthread_mutex_init(&control->forkv[i], NULL);
		i++;
	}
	i = 0;
	while (i < control->nph)
	{
			control->philov[i] = create_thread_struct(control, i + 1);
			i++;
	}
	i = 0;
	while (i < control->nph)
	{
		pthread_create(&control->thv[i], NULL, &thread_execute, control->philov[i]);
		i++;
	}
	i = 0;
	while (i < control->nph)
	{
		pthread_join(control->thv[i], NULL);
		i++;
	}
// daqui pra baixo é tudo free
	return (0);
}
/* 
	i = 0;
	while (i < control->nph)
	{
		pthread_detach(control->thv[i]);
		i++;
	}
*/
