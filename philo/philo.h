/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:46:28 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 21:58:00 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_all	t_all;

typedef enum e_state
{
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DEAD,
	S_LEFT_FORK,
	S_RIGHT_FORK,
	S_END_dining
}	t_state;

typedef struct s_philo
{
	pthread_t		thread_philo;
	long			id;
	int				fork[2];
	t_all			*all;
	long			nbr_meals_done;
	pthread_mutex_t	meal_lock;
	time_t			last_meal;
}				t_philo;

typedef struct s_all
{
	pthread_t		thread_all;
	time_t			start_dining; //to calculate life time
	long			nbr_philo; //1st arg
	long			time_to_die; //2nd arg
	long			time_to_eat; //3rd arg
	long			time_to_sleep; //4th arg
	long			time_must_eat; //5th optional arg
	t_philo			**philo;
	bool			finished;
	pthread_mutex_t	finished_lock;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	output_lock;
}				t_all;

void	*dining_routines(void *data);

bool	is_valid_args(int argc, char **argv);

long	ft_atol(const char *str);

bool	ft_isdigit(int c);

t_all	*init_all(int argc, char **argv);

void	*error_msg_null(char *str, t_all *all);

int		datetime_now(void);

int		get_time_ms(int start_dining);

void	show_status(t_philo *philo, t_state status);

void	thread_sleep(t_all *all, time_t duration);

void	*free_all(t_all *all);

bool	has_dinner_finish(t_all *all);

void	*finish_routines(void *data);

void	set_finished(t_all *all, bool value);

void	set_last_meal_prop(t_philo *philo, time_t value);

void	set_incr_meals_done(t_philo *philo);

bool	is_param_valid(t_all *all);

long	handle_thinking_time(t_philo *philo);

#endif
