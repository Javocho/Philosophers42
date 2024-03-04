/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:40 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 21:55:21 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_meal_prop(t_philo *philo, time_t value)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = value;
	pthread_mutex_unlock(&philo->meal_lock);
}

void	set_finished(t_all *all, bool value)
{
	pthread_mutex_lock(&all->finished_lock);
	all->finished = value;
	pthread_mutex_unlock(&all->finished_lock);
}

void	set_incr_meals_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->nbr_meals_done++;
	pthread_mutex_unlock(&philo->meal_lock);
}

bool	has_dinner_finish(t_all *all)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&all->finished_lock);
	if (all->finished == true)
		result = true;
	pthread_mutex_unlock(&all->finished_lock);
	return (result);
}
