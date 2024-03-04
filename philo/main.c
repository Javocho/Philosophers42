/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:36 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 21:55:24 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_dining(t_all *all);
static bool	start_dining(t_all *all);

int	main(int argc, char **argv)
{
	t_all	*all;

	all = NULL;
	if (is_valid_args(argc, argv) == false)
		return (EXIT_FAILURE);
	all = init_all(argc, argv);
	if (!all)
		return (EXIT_FAILURE);
	if (start_dining(all) == false)
		return (EXIT_FAILURE);
	end_dining(all);
	return (EXIT_SUCCESS);
}

static void	end_dining(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nbr_philo)
	{
		pthread_join(all->philo[i]->thread_philo, NULL);
		i++;
	}
	if (all->nbr_philo > 1)
		pthread_join(all->thread_all, NULL);
	free_all(all);
}

static bool	start_dining(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nbr_philo)
	{
		if (pthread_create(&all->philo[i]->thread_philo, NULL,
				&dining_routines, all->philo[i]) != 0)
			return (error_msg_null("Error: Could not create thread.\n", all));
		i++;
	}
	if (all->nbr_philo > 1)
	{
		if (pthread_create(&all->thread_all, NULL, &finish_routines,
				all) != 0)
			return (error_msg_null("Error: Could not create thread.\n", all));
	}
	return (true);
}
