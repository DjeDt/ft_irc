/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:31:12 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/12 11:34:13 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	command_free(char **command)
{
	if (command[0] != NULL)
	{
		free(command[0]);
		if (command[1] != NULL)
		{
			free(command[1]);
			if (command[2] != NULL)
				free(command[2]);
		}
	}
}

int		command_size(char *command)
{
	int i;

	i = 0;
	while (command[i] && _isspace(command[i]) != 0)
		i++;
	return (i);
}

bool	command_split(char **command, const char *final)
{
	int		size;
	char	*ptr;

	ptr = (char*)final;
	size = command_size(ptr);
	if (size > 0)
	{
		if (!(command[0] = _strndup(ptr, size)))
			return (false);
		ptr = ptr + (size + 1);
		size = command_size(ptr);
		if (size > 0)
		{
			if (!(command[1] = _strndup(ptr, size)))
				return (false);
			ptr = ptr + (size + 1);
			size = _strlen(ptr);
			if (size > 0)
			{
				if (!(command[2] = _strndup(ptr, size)))
					return (false);
			}
		}
		return (true);
	}
	return (false);
}
