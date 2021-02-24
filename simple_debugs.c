/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_debugs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldeta <user@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:05:47 by bcosters          #+#    #+#             */
/*   Updated: 2021/02/24 15:07:21 by mvaldeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void debug(const char *s, char *name)
{
    write(1, name, ft_strlen(name));
    write(1, "\t", 1);
    write(1, "DEBUG:\t", 7);
    write(1, s, ft_strlen(s));
    write(1, "\n", 1);
    write(1, "[DEBUG]\n", 8);
}
void ft_putchar(char c)
{
    write(1, &c, 1);
}
void ft_putnbr(int nb)
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
void debug_number(int i)
{
    write(1, "Number:\t", ft_strlen("Number:\t"));
    ft_putnbr(i);
    write(1, "\n", 1);
}
