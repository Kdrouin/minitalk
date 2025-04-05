/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadrouin <kadrouin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 03:28:12 by kadrouin          #+#    #+#             */
/*   Updated: 2024/12/07 11:50:40 by kadrouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(const char *c)
{
	int	len;

	len = 0;
	if (!c)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (c[len] != '\0')
	{
		write(1, &c[len], 1);
		len++;
	}
	return (len);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
