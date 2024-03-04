/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:48:00 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 21:52:41 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	datetime_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_time_ms(int start_dining)
{
	return (datetime_now() - start_dining);
}

void	thread_sleep(t_all *all, time_t duration)
{
	time_t	time_wake_up;

	time_wake_up = datetime_now() + duration;
	while (datetime_now() < time_wake_up)
	{
		if (has_dinner_finish(all))
			break ;
		usleep(100);
	}
}

long	handle_thinking_time(t_philo *philo)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->meal_lock);
	time_to_think = (philo->all->time_to_die - (datetime_now()
				- philo->last_meal) - philo->all->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_to_think > 500)
		return (200);
	else
		return (1);
}
