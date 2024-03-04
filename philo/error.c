/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:47:09 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/03/04 20:47:13 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	*error_msg_null(char *str, t_table *table)
{
	if (table)
		free_table(table);
	printf("%s", str);
	return (NULL);
}
