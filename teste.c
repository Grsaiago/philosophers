/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:46:10 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/17 22:57:39 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_thread_struct(t_control *control, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
			exit (1);
	philo->forkv = control->forkv;
	philo->mutexv = control->mutexv;
	philo->nph = control->nph;
	philo->time_to_die = 500;
	philo->time_to_eat = 500;
	philo->time_to_sleep = 500;
	philo->phid = i;
	philo->forks = 0;
	philo->prev_f = i - 1;
//	isso abaixo nunca vai rolar pq o i min é 1.	
//	if (philo->prev_f < 0)
//		philo->prev_f = ((philo->prev_f % control->nph) * -1) - control->nph;
	philo->next_f = i;
	if (philo->next_f >= control->nph)
			philo->next_f = philo->next_f % control->nph;
	return(philo);
}

void	*thread_execute(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	printf("Thread %d criada\n", philo->phid);
	while(42)
	{
		if (philo->phid == philo->nph)
		{
			pthread_mutex_lock(&philo->mutexv[philo->prev_f]);
			printf("%d has taken a fork\n", philo->phid);
			pthread_mutex_lock(&philo->mutexv[philo->next_f]);
		}
		else 
		{
			pthread_mutex_lock(&philo->mutexv[philo->next_f]);
			printf("%d has taken a fork\n", philo->phid);
			pthread_mutex_lock(&philo->mutexv[philo->prev_f]);
		}
		printf("%d is eating\n", philo->phid);
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->mutexv[philo->prev_f]);
		pthread_mutex_unlock(&philo->mutexv[philo->next_f]);
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
	control->thv = (pthread_t *)malloc(sizeof(pthread_t *) * (control->nph + 1)); // array in which every position will be a thread id
	control->forkv = (int *)malloc(sizeof(int) * control->nph); // creating an int array with every fork
	control->philov = (t_philo **)malloc(sizeof(t_philo *) * (control->nph + 1)); // creating a vector with the address of every philo struct
	control->mutexv = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (control->nph + 1)); //create mutex vector to control everything, alongside the forkv
	while (i < control->nph) // initialize mutexes
	{
		pthread_mutex_init(&control->mutexv[i], NULL);
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
	i = 0;
	while (i < control->nph)
	{
		free(control->philov[i]);
		i++;
	}
	if (control->philov)
		free(control->philov);
	if (control->thv)
		free(control->thv);
	if (control->forkv)
		free(control->forkv);
	if (control->mutexv)
		free(control->mutexv);
	printf("Sizeof pthread_t > |%ld|\n", sizeof(pthread_t)); //menos esse né
	pthread_mutex_destroy(&mutex);
	return (0);
}
