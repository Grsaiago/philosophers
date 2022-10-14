/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:46:10 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/14 19:48:24 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_thread_struct(t_control *control, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->phid = i;
	philo->forks = 0;
	philo->prev_f = i - 1;
	if (philo->prev_f < 0)
		philo->prev_f = (philo->prev_f % control->nph) * -1;
	philo->next_f = i + 1;
	if (philo->next_f >= control->nph)
			philo->next_f = philo->next_f % control->nph;
	return(philo);
}

void	*thread_execute(void *ptr)
{
	t_control		*control;
//	printf("Thread %d criada\n", *phid);
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
	control = &(t_control){0};
	control->nph = atoi(argv[1]);
	control->thv = (pthread_t *)malloc(sizeof(pthread_t *) * (control->nph + 1));
	control->phidv = (int *)malloc(sizeof(int) * control->nph);
	control->philov = (t_philo **)malloc(sizeof(t_philo *) * (control->nph + 1));
	while (i < control->nph)
	{
			control->philov[i] = create_thread_struct(control, i);
			i++;
	}
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < control->nph)
	{
		control->phidv[i] = i;
		pthread_create(&control->thv[i], NULL, &thread_execute, &control->philov[i]);
		i++;
	}

	i = 0;
	while (i < control->nph)
	{
		pthread_join(control->thv[i], NULL);
		i++;
	}
	free(control->thv);
	free(control->phidv);
	printf("Sizeof pthread_t > |%ld|\n", sizeof(pthread_t));
	pthread_mutex_destroy(&mutex);
	return (0);
}
