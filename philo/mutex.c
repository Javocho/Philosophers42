/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:40 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 20:47:41 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	set_last_meal_prop(t_philo *philo, time_t value)
{
	pthread_mutex_lock(&philo->general_meal_lock);
	philo->last_meal = value;
	pthread_mutex_unlock(&philo->general_meal_lock);
}

void	set_dinner_end_prop(t_table *table, bool value)
{
	pthread_mutex_lock(&table->dinner_end_lock);
	table->dinner_end = value;
	pthread_mutex_unlock(&table->dinner_end_lock);
}

void	increment_times_eat_prop(t_philo *philo)
{
	pthread_mutex_lock(&philo->general_meal_lock);
	philo->nbr_meals_done++;
	pthread_mutex_unlock(&philo->general_meal_lock);
}

bool	has_dinner_finish(t_table *table)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&table->dinner_end_lock);
	if (table->dinner_end == true)
		result = true;
	pthread_mutex_unlock(&table->dinner_end_lock);
	return (result);
}
