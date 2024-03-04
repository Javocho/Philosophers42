/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:33 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 22:00:16 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void				sort_fork_by_philo(t_philo *philo);
static bool				init_philo(t_all *all);
static bool				init_mutex(t_all *all);
static pthread_mutex_t	*init_forks(t_all *all);

t_all	*init_all(int argc, char **argv)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	if (!all)
		return (error_msg_null("Error: Could not allocate memory.\n", NULL));
	all->nbr_philo = ft_atol(argv[1]);
	all->time_to_die = ft_atol(argv[2]);
	all->time_to_eat = ft_atol(argv[3]);
	all->time_to_sleep = ft_atol(argv[4]);
	all->time_must_eat = -1;
	if (argc == 6)
		all->time_must_eat = ft_atol(argv[5]);
	all->finished = false;
	all->start_dining = datetime_now();
	if (init_philo(all) == false || all->philo == NULL)
		return (NULL);
	if (init_mutex(all) == false || is_param_valid(all) == false)
		return (NULL);
	return (all);
}

static bool	init_philo(t_all *all)
{
	t_philo	**philos;
	long	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * all->nbr_philo);
	if (philos == NULL)
		return (error_msg_null("Error: Could not allocate memory.\n", NULL));
	while (i < all->nbr_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (error_msg_null("Error: Could not allocate memory.\n", \
			NULL));
		philos[i]->all = all;
		philos[i]->id = i;
		philos[i]->nbr_meals_done = 0;
		sort_fork_by_philo(philos[i]);
		if (pthread_mutex_init(&philos[i]->meal_lock, 0) != 0)
			return (error_msg_null("Error: Could not create mutex.\n", NULL));
		i++;
	}
	all->philo = philos;
	return (true);
}

static pthread_mutex_t	*init_forks(t_all *all)
{
	pthread_mutex_t	*forks;
	long			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * all->nbr_philo);
	if (!forks)
		return (error_msg_null("Error: Could not allocate memory.\n", NULL));
	while (i < all->nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_msg_null("Error: Could not create mutex.\n", NULL));
		i++;
	}
	return (forks);
}

static bool	init_mutex(t_all *all)
{
	all->fork_lock = init_forks(all);
	if (!all->fork_lock)
		return (false);
	if (pthread_mutex_init(&all->finished_lock, 0) != 0)
		return (error_msg_null("Error: Could not create mutex.\n", NULL));
	if (pthread_mutex_init(&all->output_lock, 0) != 0)
		return (error_msg_null("Error: Could not create mutex.\n", NULL));
	return (true);
}

static void	sort_fork_by_philo(t_philo *philo)
{
	philo->fork[0] = philo->id;
	if (philo->all->nbr_philo > 1)
	{
		philo->fork[1] = (philo->id + 1) % philo->all->nbr_philo;
		if (philo->id % 2 != 0)
		{
			philo->fork[0] = (philo->id + 1) % philo->all->nbr_philo;
			philo->fork[1] = philo->id;
		}
	}
}
