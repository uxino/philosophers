/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:06:57 by museker           #+#    #+#             */
/*   Updated: 2023/09/12 11:39:04 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex_fork);
		printf("%lld %d has taken a fork\n",
			get_time_passed(philo->info), philo->id);
		pthread_mutex_lock(&philo->left->mutex_fork);
		printf("%lld %d has taken a fork\n",
			get_time_passed(philo->info), philo->id);
		printf("%lld %d is eating\n", get_time_passed(philo->info), philo->id);
		philo->eaten++;
		philo->last_meal = get_time();
		usleep(philo->info->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex_fork);
		pthread_mutex_unlock(&philo->left->mutex_fork);
		printf("%lld %d is sleeping\n",
			get_time_passed(philo->info), philo->id);
		usleep_and_check(philo->info->time_to_sleep * 1000, philo);
		printf("%lld %d is thinking\n",
			get_time_passed(philo->info), philo->id);
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

void	start_thread(t_philo *philo, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_philo)
	{
		pthread_create(&philo->thread, NULL, life_of_philo, philo);
		philo = philo->left;
		usleep(100);
	}
}

void	check_dead(t_philo *philo, t_info *info)
{
	while (1)
	{
		if ((get_time() - philo->last_meal) > info->time_to_die)
		{
			pthread_mutex_lock(&info->mutex_dead);
			printf("%lld %d died\n", get_time_passed(info), philo->id);
			pthread_mutex_unlock(&info->mutex_dead);
			exit(1);
		}
	}
}

void	usleep_and_check(long long utime, t_philo *philo)
{
	long long	i;

	i = 0;
	while (i < utime)
	{
		usleep(100);
		i += 100;
		if ((get_time() - philo->last_meal) > philo->info->time_to_die)
		{
			// pthread_mutex_lock(&philo->info->mutex_dead);
			// printf("%lld %d died\n", get_time_passed(philo->info), philo->id);
			// pthread_mutex_unlock(&philo->info->mutex_dead);
			// exit(1);
		}
	}
}
