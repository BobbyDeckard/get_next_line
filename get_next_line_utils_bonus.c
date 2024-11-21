/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeulema <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:56:55 by imeulema          #+#    #+#             */
/*   Updated: 2024/11/21 11:59:58 by imeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_null(char *str)
{
	free(str);
	return (NULL);
}

unsigned int	gnl_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	line_complete(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}
