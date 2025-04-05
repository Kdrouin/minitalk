/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_number.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadrouin <kadrouin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 03:29:23 by kadrouin          #+#    #+#             */
/*   Updated: 2024/12/07 11:50:43 by kadrouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr("-2147483648");
		return (count);
	}
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	else
		count += ft_putchar(n + '0');
	return (count);
}

int	ft_putunbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putunbr(n / 10);
		count += ft_putunbr(n % 10);
	}
	else
		count += ft_putchar(n + '0');
	return (count);
}

int	ft_putptr(va_list args, int count)
{
	unsigned long long	n;

	n = va_arg(args, unsigned long long);
	if (n == 0)
		return (ft_putstr("(nil)"));
	count += ft_putstr("0x");
	count += ft_putnbr_base(n, "0123456789abcdef");
	return (count);
}

int	ft_putnbr_base(unsigned long long n, char *base)
{
	int					count;
	unsigned long long	len;

	count = 0;
	len = ft_strlen(base);
	if (n >= len)
		count += ft_putnbr_base(n / len, base);
	ft_putchar(base[n % len]);
	count++;
	return (count);
}
