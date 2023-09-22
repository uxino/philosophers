/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:43:38 by museker           #+#    #+#             */
/*   Updated: 2023/09/16 16:16:01 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
		return (-1);
	return (result);
}

int	check_arguman(char **argv)
{
	int	i;

	i = -1;
	if (ft_atoi(argv[0]) == 0)
		return (-1);
	if (argv[4] && ft_atoi(argv[4]) == 0)
		return (-1);
	while (argv[++i])
		if (ft_atoi(argv[i]) == -1)
			return (-1);
	return (0);
}

unsigned long	get_ms(t_info *pi)
{
	gettimeofday(&pi->tv, NULL);
	return ((pi->tv.tv_usec / 1000 + pi->tv.tv_sec * 1000) - pi->start_time);
}

void	ms_sleep(t_philo *p, int time)
{
	unsigned long	dest_time;

	dest_time = get_ms(p->info) + time;
	while (get_ms(p->info) < dest_time)
		usleep(100);
}
