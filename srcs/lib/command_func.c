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

#include "lib.h"

int		command_size(char *command)
{
	int i;

	i = 0;
	while (command[i] != '\0' && ft_isspace(command[i]) == false)
		i++;
	return (i);
}

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

bool	command_split(char **command, const char *final)
{
	int		size;
	char	*ptr;

	ptr = (char*)final;
	size = command_size(ptr);
	if (size > 0)
	{
		if (!(command[0] = ft_strndup(ptr, size)))
			return (false);
		ptr = ptr + (size + 1);
		size = command_size(ptr);
		if (size > 0)
		{
			if (!(command[1] = ft_strndup(ptr, size)))
				return (false);
			ptr = ptr + (size + 1);
			size = ft_strlen(ptr);
			if (size > 0)
			{
				if (!(command[2] = ft_strndup(ptr, size)))
					return (false);
			}
		}
		return (true);
	}
	return (false);
}
