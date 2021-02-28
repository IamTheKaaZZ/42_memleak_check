/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_debugs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:05:47 by bcosters          #+#    #+#             */
/*   Updated: 2021/02/28 14:28:02 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
**  Helper functions
*/

static void ft_putchar(char c)
{
    write(1, &c, 1);
}
static void ft_putnbr(int nb)
{
    if (nb < 0)
    {
        ft_putchar('-');
        ft_putnbr(-nb);
    }
    else if (nb > 9)
    {
        ft_putnbr(nb / 10);
        ft_putnbr(nb % 10);
    }
    else
    {
        ft_putchar(nb + '0');
    }
}

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

/*
**  Debug functions
*/

void debug_str(const char *s, char *name)
{
    write(1, "DEBUG_STR OF:\t", 14);
    write(1, name, ft_strlen(name));
    write(1, ":\t", 2);
    write(1, "\"", 1);
    write(1, s, ft_strlen(s));
    write(1, "\"", 1);
    write(1, "\n[END OF DEBUG_STR]\n", 20);
}
void debug_number(int i, char *name)
{
    write(1, "DEBUG_NBR OF:\t", 14);
    write(1, name, ft_strlen(name));
    write(1, ":\t", ft_strlen(":\t"));
    write(1, "\"", 1);
    ft_putnbr(i);
    write(1, "\"", 1);
    write(1, "\n[END OF DEBUG_NBR]\n", 20);
}
