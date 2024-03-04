/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:49 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 21:58:00 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo(t_philo *philo);
static void	ft_think(t_philo *philo, bool log);
static void	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);

void	*dining_routines(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->all->time_must_eat == 0)
		return (NULL);
	set_last_meal_prop(philo, philo->all->start_dining);
	if (philo->all->nbr_philo == 1)
		return (one_philo(philo));
	if (philo->id % 2 != 0)
		ft_think(philo, false);
	while (has_dinner_finish(philo->all) == false)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo, true);
	}
	return (NULL);
}

static void	ft_sleep(t_philo *philo)
{
	show_status(philo, S_SLEEPING);
	thread_sleep(philo->all, philo->all->time_to_sleep);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->fork_lock[philo->fork[0]]);
	show_status(philo, S_LEFT_FORK);
	pthread_mutex_lock(&philo->all->fork_lock[philo->fork[1]]);
	show_status(philo, S_RIGHT_FORK);
	show_status(philo, S_EATING);
	set_last_meal_prop(philo, datetime_now());
	thread_sleep(philo->all, philo->all->time_to_eat);
	if (has_dinner_finish(philo->all) == false)
		set_incr_meals_done(philo);
	pthread_mutex_unlock(&philo->all->fork_lock[philo->fork[1]]);
	pthread_mutex_unlock(&philo->all->fork_lock[philo->fork[0]]);
}

static void	ft_think(t_philo *philo, bool log)
{
	time_t	time_thinking;

	time_thinking = handle_thinking_time(philo);
	if (log == true)
		show_status(philo, S_THINKING);
	thread_sleep(philo->all, time_thinking);
}

static void	*one_philo(t_philo *philo)
{
	show_status(philo, S_LEFT_FORK);
	thread_sleep(philo->all, philo->all->time_to_die);
	show_status(philo, S_DEAD);
	return (NULL);
}
