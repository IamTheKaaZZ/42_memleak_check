/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlc_internals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:56:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/20 10:56:37 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_leak_checker.h"

// ================================= INTERNAL =================================

t_call	*find_empty_position(void)
{
	int	i;

	i = -1;
	while (++i < ARRAY_SIZE)
		if (g_allocs_array[i].address == 0)
			return (&(g_allocs_array[i]));
	return (0);
}

void	add_call(t_call *call)
{
	t_call	*position;

	position = find_empty_position();
	if (position == 0)
	{
		fprintf(stderr, "There is no room left for `g_allocs_array`\n"
			"Please increase its size\n");
		exit(1);
	}
	memcpy(position, call, sizeof(t_call));
}

void	remove_call(long address)
{
	int	i;

	i = -1;
	while (++i < ARRAY_SIZE)
	{
		if (g_allocs_array[i].address == address)
		{
			g_allocs_array[i].address = 0;
			g_allocs_array[i].size = 0;
			g_allocs_array[i].line[0] = '\0';
			return ;
		}
	}
	fprintf(stderr, "Trying to free memory that have already freed or "
		"haven't ever allocated\n"
		"Address 0x%lx not found in `g_allocs_array`\n", address);
	exit(2);
}
