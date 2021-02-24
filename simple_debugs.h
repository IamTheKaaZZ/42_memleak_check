/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_debugs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:07:42 by bcosters          #+#    #+#             */
/*   Updated: 2021/02/17 12:09:27 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_DEBUGS_H
# define SIMPLE_DEBUGS_H

# include <unistd.h>
void debug(const char *s, char *name);
void debug_number(int i);

#endif