/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:30 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 21:52:41 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nbr_philo)
	{
		pthread_mutex_destroy(&all->philo[i]->meal_lock);
		pthread_mutex_destroy(&all->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&all->finished_lock);
	pthread_mutex_destroy(&all->output_lock);
}

void	*free_all(t_all *all)
{
	int	i;

	if (!all)
		return (NULL);
	destroy_mutexes(all);
	if (all->fork_lock != NULL)
		free(all->fork_lock);
	if (all->philo)
	{
		i = 0;
		while (i < all->nbr_philo)
		{
			free(all->philo[i]);
			i++;
		}
		free(all->philo);
	}
	free(all);
	return (NULL);
}
