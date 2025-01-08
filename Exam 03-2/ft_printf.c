/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:44:51 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/08 11:12:01 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

static void	ft_putchar(char c, int *cnt)
{
	(*cnt) += write(1, &c, 1);
}

static void	ft_putstr(char *s, int *cnt)
{
	int	i;

	i = 0;
	while (s[i])
		ft_putchar(s[i++], cnt);
}

static void	ft_putnbr(int n, int *cnt)
{
	if (n == INT_MIN)
	{
		ft_putstr("-2147483648", cnt);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		(*cnt)++;
		ft_putchar('-', cnt);
	}
	if (n >= 10)
		ft_putnbr(n / 10, cnt);
	ft_putchar((n % 10) + '0', cnt);
}

static void	ft_puthex(unsigned int n, char *base, int *cnt)
{
	if (n >= 16)
		ft_puthex(n / 16, base, cnt);
	ft_putchar(base[n % 16], cnt);
}

int	ft_printf(const char *str, ...)
{
	int		cnt;
	int		i;
	va_list	args;

	cnt = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 's')
				ft_putstr(va_arg(args, char *), &cnt);
			else if (str[i] == 'd')
				ft_putnbr(va_arg(args, int), &cnt);
			else if (str[i] == 'x')
				ft_puthex(va_arg(args, unsigned int), "0123456789abcdef", &cnt);
		}
		else
			ft_putchar(str[i], &cnt);
		i++;
	}
	va_end(args);
	return (cnt);
}

int	main(int argc, char **argv)
{
	int	cnt;

	if (argc != 2)
		return (0);
	cnt = ft_printf("String: %s\n", argv[1]);
	cnt = ft_printf("Cnt str: %d\n", cnt);
	ft_printf("Cnt int: %d\n", cnt);
	cnt = ft_printf("Hex: %x\n", 15);
	ft_printf("cnt hex: %d\n", cnt);
	return (0);
}
