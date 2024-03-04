/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:30 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 20:55:25 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static void	free_mutex(t_table *table);

void	*free_table(t_table *table)
{
	int	i;

	if (!table)
		return (NULL);
	free_mutex(table);
	if (table->fork_lock != NULL)
		free(table->fork_lock);
	if (table->philo)
	{
		i = 0;
		while (i < table->nbr_philo)
		{
			free(table->philo[i]);
			i++;
		}
		free(table->philo);
	}
	free(table);
	return (NULL);
}

static void	free_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->philo[i]->general_meal_lock);
		pthread_mutex_destroy(&table->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&table->dinner_end_lock);
	pthread_mutex_destroy(&table->log_lock);
}
