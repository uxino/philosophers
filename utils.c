/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:06:57 by museker           #+#    #+#             */
/*   Updated: 2023/09/16 16:17:42 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo *p)
{
	pthread_mutex_lock(&p->info->forks[p->id]);
	pthread_mutex_lock(&p->info->mutex_dead);
	printf("%lu %d has taken a fork\n", get_ms(p->info), p->id + 1);
	pthread_mutex_unlock(&p->info->mutex_dead);
	pthread_mutex_lock(&p->info->forks[(p->id + 1) % p->info->number_philo]);
	pthread_mutex_lock(&p->info->mutex_dead);
	printf("%lu %d has taken a fork\n", get_ms(p->info), p->id + 1);
	printf("%lu %d is eating\n", get_ms(p->info), p->id + 1);
	pthread_mutex_unlock(&p->info->mutex_dead);
	pthread_mutex_lock(&p->info->eaten);
	p->eaten++;
	p->info->eat_count++;
	p->last_meal = get_ms(p->info);
	pthread_mutex_unlock(&p->info->eaten);
	ms_sleep(p, p->info->time_to_eat);
	printf("%lu %d is sleeping\n", get_ms(p->info), p->id + 1);
	pthread_mutex_unlock(&p->info->forks[p->id]);
	pthread_mutex_unlock(&p->info->forks[(p->id + 1) % p->info->number_philo]);
	pthread_mutex_lock(&p->info->mutex_dead);
	pthread_mutex_unlock(&p->info->mutex_dead);
	ms_sleep(p, p->info->time_to_sleep);
	pthread_mutex_lock(&p->info->mutex_dead);
	printf("%lu %d is thinking\n", get_ms(p->info), p->id + 1);
	pthread_mutex_unlock(&p->info->mutex_dead);
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		write_status(philo);
	}
	return (NULL);
}

void	join_thread(t_philo *philo, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_philo)
		pthread_join(philo->thread, NULL);
}

void	start_thread(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_philo)
	{
		pthread_create(&info->philos[i].thread, NULL,
			life_of_philo, &info->philos[i]);
		usleep(100);
	}
}
