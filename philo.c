/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:44:54 by museker           #+#    #+#             */
/*   Updated: 2023/09/12 11:59:22 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long long	get_time_passed(t_info *ph)
{
	return (get_time() - ph->start_time);
}

t_philo	*set_philosophers(t_info *info)
{
	t_philo	*first;
	t_philo	*temp;
	int		i;

	i = 0;
	first = malloc(sizeof(t_philo));
	first->id = ++i;
	first->last_meal = 9999999999999;
	pthread_mutex_init(&first->mutex_fork, NULL);
	first->info = info;
	temp = first;
	while (i < info->number_philo)
	{
		usleep(100);
		temp->left = malloc(sizeof(t_philo));
		temp->left->id = ++i;
		temp->left->last_meal = 9223372036854775807LL;
		pthread_mutex_init(&temp->left->mutex_fork, NULL);
		temp->left->info = info;
		temp = temp->left;
	}
	temp->left = first;
	return (first);
}

t_info	*set_info(int argc, char *argv[])
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->number_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat_flag = 0;
	pthread_mutex_init(&info->mutex_dead, NULL);
	if (argc == 6)
	{
		info->must_eat_flag = 1;
		info->number_must_eat = ft_atoi(argv[5]);
	}
	return (info);
}

int	main(int argc, char *argv[])
{
	t_info	*info;
	t_philo	*first;

	if (argc != 5 && argc != 6)
		return (0);
	info = set_info(argc, argv);
	first = set_philosophers(info);
	info->start_time = get_time();
	start_thread(first, info);
	int i = 0;
	while (1)
	{
		i++;
		usleep(100);
		if ((get_time() - first->last_meal) > first->info->time_to_die)
		{
			pthread_mutex_lock(&first->info->mutex_dead);
			printf("%lld %d died\n", get_time_passed(first->info), i % first->info->number_philo);
			pthread_mutex_unlock(&first->info->mutex_dead);
			exit(1);
		}
	}
	// join_thread(first, info);
	check_dead(first, info);
}
