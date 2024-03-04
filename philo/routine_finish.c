/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:52 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 21:58:00 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	dinner_finished_reached(t_all *all);

void	*finish_routines(void *data)
{
	t_all			*all;

	all = (t_all *)data;
	if (all->time_must_eat == 0)
		return (NULL);
	set_finished(all, false);
	while (true)
	{
		if (dinner_finished_reached(all) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static bool	kill_philo(t_philo *philo)
{
	if ((datetime_now() - philo->last_meal) >= philo->all->time_to_die)
	{
		show_status(philo, S_DEAD);
		set_finished(philo->all, true);
		pthread_mutex_unlock(&philo->meal_lock);
		return (true);
	}
	return (false);
}

static bool	dinner_finished_reached(t_all *all)
{
	int		i;
	bool	eat_enough;

	i = 0;
	eat_enough = true;
	while (i < all->nbr_philo)
	{
		pthread_mutex_lock(&all->philo[i]->meal_lock);
		if (kill_philo(all->philo[i]) == true)
			return (true);
		if (all->time_must_eat != -1)
			if (all->philo[i]->nbr_meals_done < all->time_must_eat)
				eat_enough = false;
		pthread_mutex_unlock(&all->philo[i]->meal_lock);
		i++;
	}
	if (all->time_must_eat != -1 && eat_enough == true)
	{
		set_finished(all, true);
		return (true);
	}
	return (false);
}
