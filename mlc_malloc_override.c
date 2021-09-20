/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlc_malloc_override.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:59:53 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/20 11:00:49 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_leak_checker.h"

// ================================== MALLOC ==================================

void	malloc_init(void)
{
	g_real_malloc = (void *(*)(unsigned long))dlsym(RTLD_NEXT, "malloc");
	if (g_real_malloc == 0)
		fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
	memset(&g_allocs_array, 0, sizeof(g_allocs_array));
}

char	*split_to_only_func(char *s)
{
	int	len;
	int	space_count;
	int	i;

	len = strlen(s);
	space_count = 0;
	i = len - 1;
	while (i-- >= 0)
	{
		if (s[i] == ' ')
			space_count++;
		if (space_count == 3)
			return (s + i);
	}
	return (s);
}

void	cp_stack(char *dst, char **s_arr, int size)
{
	int		total_len;
	char	*function;
	int		current_len;
	int		i;

	total_len = 0;
	i = -1;
	while (++i < size)
	{
		function = split_to_only_func(s_arr[i]);
		current_len = strlen(function);
		total_len += current_len;
		if (total_len + 2 > LINE_LEN)
			return ;
		if (total_len != current_len)
		{
			dst[0] = '\n';
			dst += 1;
		}
		strncpy(dst, function, current_len + 1);
		dst += current_len;
	}
}

void	*malloc(unsigned long size)
{
	void	*p;
	t_call	call;
	void	*callstack[128];
	int		frames;
	char	**strs;

	p = 0;
	if (g_real_malloc == 0)
		malloc_init();
	p = g_real_malloc(size);
	call.address = (long)p;
	call.size = size;
	call.line[0] = '\0';
	frames = backtrace(callstack, 128);
	strs = backtrace_symbols(callstack, frames);
	cp_stack(call.line, strs, frames);
	add_call(&call);
	g_malloc_counter++;
	return (p);
}
