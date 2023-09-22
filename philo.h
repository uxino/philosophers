/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:42:18 by museker           #+#    #+#             */
/*   Updated: 2023/09/16 16:15:37 by museker          ###   ########.fr       */
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
	unsigned long	last_meal;
	pthread_t		thread;
	struct s_info	*info;
	int				is_dead;
}	t_philo;

typedef struct s_info
{
	unsigned long		start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					number_philo;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					must_eat_flag;
	int					number_must_eat;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		eaten;
	int					eat_count;
	struct timeval		tv;
}	t_info;

//philo
void				set_philosophers(t_info *info);
t_info				*set_info(int argc, char *argv[]);
void				main_thread(t_info *info);

//utils
void				write_status(t_philo *p);
void				*life_of_philo(void *arg);
void				join_thread(t_philo *philo, t_info *info);
void				start_thread(t_info *info);

//ft_atoi
long				ft_atoi(char *str);
int					check_arguman(char **argv);
unsigned long		get_ms(t_info *pi);
void				ms_sleep(t_philo *p, int time);
#endif