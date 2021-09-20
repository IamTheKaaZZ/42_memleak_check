/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_leak_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:31:57 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/20 11:43:40 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Rostyslav Druzhchenko on 05.09.2020.
//
#include "malloc_leak_checker.h"

int	g_malloc_counter = 0;

// ================================== PUBLIC ==================================

void	check_leaks(void)
{
	int	total;

	if (g_malloc_counter != 0)
	{
		total = total_leaks_size();
		fprintf(stderr,
			"\nLEAKS: there are %d leaks. TOTAL size: %d bytes\n\n",
			g_malloc_counter, total);
		print_allocs();
	}
}

// =================================== FREE ===================================

static void	free_init(void)
{
	g_real_free = (void (*)(void *))dlsym(RTLD_NEXT, "free");
	if (g_real_free == 0)
		fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
}

void	free(void *p)
{
	if (g_real_free == 0)
		free_init();
	remove_call((long)p);
	g_real_free(p);
	g_malloc_counter--;
}
