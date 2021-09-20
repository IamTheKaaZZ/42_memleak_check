/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_leak_checker.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:34:23 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/20 11:40:46 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_LEAK_CHECKER_H
# define MALLOC_LEAK_CHECKER_H

/*
**	Memory leak checker in C, courtesy of https://gist.github.com/drrost
*/

# include <stdio.h>
# include <dlfcn.h>
# include <execinfo.h>
# include <string.h>
# include <stdlib.h>

extern int	g_malloc_counter;

# define LINE_LEN 1024

typedef struct s_call
{
	long			address;
	unsigned long	size;
	char			line[LINE_LEN];
}	t_call;

# define ARRAY_SIZE 1024

t_call		g_allocs_array[ARRAY_SIZE];
static void	*(*g_real_malloc)(unsigned long) = 0;
static void	(*g_real_free)(void *) = 0;

/*
**	HELPER FUNCTIONS
*/

int			total_leaks_size(void);
void		print_allocs(void);
t_call		*find_empty_position(void);
void		add_call(t_call *call);
void		remove_call(long address);
void		print_call(t_call *call);
void		print_allocs(void);
int			total_leaks_size(void);
void		malloc_init(void);
char		*split_to_only_func(char *s);
void		cp_stack(char *dst, char **s_arr, int size);
void		*malloc(unsigned long size);

/*
**	Memory leak checker in C, courtesy of https://gist.github.com/drrost
*/

void		check_leaks(void);

#endif