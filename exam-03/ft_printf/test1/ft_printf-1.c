/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf-1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:47:38 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/08 15:51:10 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdarg.h>

static void	ft_putchar(char c, int *cnt)
{
	(*cnt) += write(1, &c, 1);
}

static void	ft_putstr(const char *s, int *cnt)
{
	int	i;

	i = 0;
	while (s[i])
		ft_putchar(s[i++], cnt);
}

static void	ft_putnbr(int n, int *cnt)
{
	if (n == INT_MIN)
		return (ft_putstr("-2147483648", cnt));
	if (n < 0)
	{
		ft_putchar('-', cnt);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10, cnt);
	ft_putchar((n % 10) + '0', cnt);
}

static void	ft_puthex(unsigned int n, const char *base, int *cnt)
{
	int	len;

	len = 0;
	while (base[len])
		len++;
	if (n >= len)
		ft_puthex(n / len, base, cnt);
	ft_putchar(base[n % len], cnt);
}

int	ft_printf(const char *format, ...)
{
	int		cnt;
	int		i;
	va_list	args;

	cnt = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
				ft_putstr(va_arg(args, char *), &cnt);
			else if (format[i] == 'd')
				ft_putnbr(va_arg(args, int), &cnt);
			else if (format[i] == 'x')
				ft_puthex(va_arg(args, unsigned int), "0123456789", &cnt);
		}
		else
			ft_putchar(format[i], &cnt);
		i++;
	}
	va_end(args);
	return (cnt);
}

int	main(void)
{
	int	cnt;

	cnt = ft_printf("Test\n");
	ft_printf("Cnt: %d\n", cnt);
	cnt = ft_printf("Negative: %d\n", -15);
	ft_printf("Cnt: %d\n", cnt);
	cnt = ft_printf("Positive: %d\n", 15);
	ft_printf("Cnt: %d\n", cnt);
	cnt = ft_printf("Hex: %x\n", 15);
	ft_printf("Cnt: %d\n", cnt);
	cnt = ft_printf("String: %s\n", "test");
	ft_printf("Cnt: %d\n", cnt);
}
