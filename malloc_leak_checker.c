/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_leak_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:49:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/02/17 10:50:03 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Rostyslav Druzhchenko on 05.09.2020.
//

#include <stdio.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <string.h>
#include <stdlib.h>

int malloc_counter = 0;

#define line_len 1024
typedef struct s_call {
    long address;
    unsigned long size;
    char line[line_len];
} t_call;

#define array_size 1024
t_call allocs_array[array_size];

static int total_leaks_size();
static void print_allocs();

// ================================== PUBLIC ==================================

void check_leaks() {
    if (malloc_counter != 0) {
        int total = total_leaks_size();
        fprintf(stderr,
                "\nLEAKS: there are %d leaks. TOTAL size: %d bytes\n\n",
                malloc_counter, total);
        print_allocs();
    }
}

// ================================= INTERNAL =================================

static void *(*real_malloc)(unsigned long) = 0;
static void (*real_free)(void *) = 0;

t_call *find_empty_position() {
    for (int i = 0; i < array_size; i++)
        if (allocs_array[i].address == 0)
            return &(allocs_array[i]);
    return 0;
}

static void add_call(t_call *call) {
    t_call *position = find_empty_position();
    if (position == 0) {
        fprintf(stderr, "There is no room left for `allocs_array`\n"
                        "Please increase its size\n");
        exit(1);
    }
    memcpy(position, call, sizeof(t_call));
}

static void remove_call(long address) {
    for (int i = 0; i < array_size; i++) {
        if (allocs_array[i].address == address) {
            allocs_array[i].address = 0;
            allocs_array[i].size = 0;
            allocs_array[i].line[0] = '\0';
            return;
        }
    }

    fprintf(stderr, "Trying to free memory that have already freed or "
                    "haven't ever allocated\n"
                    "Address 0x%lx not found in `allocs_array`\n", address);
    exit(2);
}

static void print_call(t_call *call) {
    fprintf(stderr, "Leak at address: 0x%lx | Leaked %ld bytes\n%s\n\n",
            call->address, call->size, call->line);
}

static void print_allocs() {
    for (int i = 0; i < array_size; i++)
        if (allocs_array[i].address != 0)
            print_call(&(allocs_array[i]));
}

static int total_leaks_size() {
    int total = 0;
    for (int i = 0; i < array_size; i++)
        if (allocs_array[i].address != 0)
            total += allocs_array[i].size;
    return total;
}

// ================================== MALLOC ==================================

static void malloc_init(void) {
    real_malloc = (void *(*)(unsigned long))dlsym(RTLD_NEXT, "malloc");
    if (real_malloc == 0)
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
    memset(&allocs_array, 0, sizeof(allocs_array));
}

static char *split_to_only_func(char *s) {
    int len = strlen(s);
    int space_count = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == ' ')
            space_count++;
        if (space_count == 3)
            return s + i;
    }
    return s;
}

static void cp_stack(char *dst, char **s_arr, int size) {
    int total_len = 0;
    for (int i = 0; i < size; i++) {
        char *function = split_to_only_func(s_arr[i]);
        int current_len = strlen(function);
        total_len += current_len;
        if (total_len + 2 > line_len)
            return;
        if (total_len != current_len) {
            dst[0] = '\n';
            dst += 1;
        }
        strncpy(dst, function, current_len + 1);
        dst += current_len;
    }
}

void *malloc(unsigned long size) {
    if (real_malloc == 0)
        malloc_init();

    void *p = 0;
    p = real_malloc(size);

    t_call call;
    call.address = (long)p;
    call.size = size;
    call.line[0] = '\0';

    void *callstack[128];
    int frames = backtrace(callstack, 128);
    char **strs = backtrace_symbols(callstack, frames);
    cp_stack(call.line, strs, frames);

    add_call(&call);
    malloc_counter++;
    return p;
}

// =================================== FREE ===================================

static void free_init(void) {
    real_free = (void (*)(void *))dlsym(RTLD_NEXT, "free");
    if (real_free == 0)
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
}

void free(void *p) {
    if (real_free == 0)
        free_init();

    remove_call((long)p);
    real_free(p);
    malloc_counter--;
}