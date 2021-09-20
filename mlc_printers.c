/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlc_printers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:57:15 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/20 10:58:33 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_leak_checker.h"

// ================================= PRINTERS =================================

void	print_call(t_call *call)
{
	fprintf(stderr, "Leak at address: 0x%lx | Leaked %ld bytes\n%s\n\n",
		call->address, call->size, call->line);
}

void	print_allocs(void)
{
	int	i;

	i = -1;
	while (++i < ARRAY_SIZE)
		if (g_allocs_array[i].address != 0)
			print_call(&(g_allocs_array[i]));
}

int	total_leaks_size(void)
{
	int	total;
	int	i;

	total = 0;
	i = -1;
	while (++i < ARRAY_SIZE)
		if (g_allocs_array[i].address != 0)
			total += g_allocs_array[i].size;
	return (total);
}
