/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:48:04 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 20:57:24 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static bool	is_valid_input(int argc, char **argv);
static bool	is_only_digit(char *arg);

bool	is_valid_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Wrong arguments. Check the subject and try again.\n");
		return (false);
	}
	if (is_valid_input(argc, argv) == false)
		return (false);
	return (true);
}

static bool	is_valid_input(int argc, char **argv)
{
	int		i;
	long	value;

	value = 0;
	i = 1;
	while (i < argc)
	{
		if (is_only_digit(argv[i]) == false)
		{
			printf("Invalid input in [%s]. Only digit accepted.\n", argv[i]);
			return (false);
		}
		value = ft_ato_long(argv[i]);
		if (value < 0 || value > LONG_MAX)
		{
			printf("Invalid input in [%ld]. Negative or so long.\n", value);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_param_valid(t_table *table)
{
	if (table->nbr_philo > 200)
	{
		printf("Invalid input in [%li].\n", table->nbr_philo);
		return (false);
	}
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
	{
		printf("Invalid input. Must be greater than 60.\n");
		return (false);
	}
	return (true);
}

static bool	is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
