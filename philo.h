/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:42:18 by museker           #+#    #+#             */
/*   Updated: 2023/09/12 11:30:30 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	mutex_fork;
	struct s_philo	*left;
	struct s_info	*info;
	int				is_dead;
}	t_philo;

typedef struct s_info
{
	long long		start_time;
	int				number_philo;
	int				time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_flag;
	int				number_must_eat;
	pthread_mutex_t	mutex_dead;
}	t_info;

//philo
long long		get_time(void);
long long		get_time_passed(t_info *ph);
t_philo			*set_philosophers(t_info *info);
t_info			*set_info(int argc, char *argv[]);

//utils
void			*life_of_philo(void *arg);
void			join_thread(t_philo *philo, t_info *info);
void			start_thread(t_philo *philo, t_info *info);
void			usleep_and_check(long long utime, t_philo *philo);
void			check_dead(t_philo *philo, t_info *info);

//ft_atoi
int				ft_atoi(char *str);
#endif