/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:44:54 by museker           #+#    #+#             */
/*   Updated: 2023/09/15 16:08:34 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philosophers(t_info *info)
{
	int		i;

	i = 0;
	info->philos = malloc(sizeof(t_philo) * info->number_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_philo);
	i = -1;
	while (++i < info->number_philo)
	{
		usleep(100);
		info->philos[i].id = i;
		info->philos[i].last_meal = 0;
		info->philos[i].info = info;
		pthread_mutex_init(&info->forks[i], NULL);
	}
}

t_info	*set_info(int argc, char *argv[])
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->number_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->start_time = get_ms(info);
	info->eat_count = 0;
	pthread_mutex_init(&info->mutex_dead, NULL);
	pthread_mutex_init(&info->eaten, NULL);
	if (argc == 6)
		info->number_must_eat = ft_atoi(argv[5]);
	else
		info->number_must_eat = -1;
	return (info);
}

void	main_thread(t_info *info)
{
	int	i;

	i = 0;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&info->eaten);
		if (info->number_must_eat != -1
			&& info->eat_count >= info->number_must_eat
			* info->number_philo)
		{
			pthread_mutex_lock(&info->mutex_dead);
			return ;
		}
		if (get_ms(info) - info->philos[i % info->number_philo].last_meal
			>= info->time_to_die)
		{
			pthread_mutex_lock(&info->mutex_dead);
			printf("%lu %d died\n", get_ms(info), (i % info->number_philo) + 1);
			return ;
		}
		pthread_mutex_unlock(&info->eaten);
		if (i == info->number_philo)
			i = 0;
	}
}

int	main(int argc, char *argv[])
{
	t_info	*info;

	if ((argc != 5 && argc != 6) || check_arguman(argv + 1) == -1)
		return (1);
	info = set_info(argc, argv);
	set_philosophers(info);
	start_thread(info);
	main_thread(info);
}
