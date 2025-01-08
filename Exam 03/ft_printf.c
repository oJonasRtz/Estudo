/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:24:19 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/07 13:32:34 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

static int	putchar(char c)
{
	return (write(1, &c, 1));
}

static int	putstr(char *s)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
		cnt += putchar(s[i++]);
	return (cnt);
}

static void	putnbr(int n, int *cnt)
{
	char	c;

	if (n == -2147483648)
	{
		(*cnt) += putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		putchar('-');
		(*cnt)++;
		n = -n;
	}
	if (n >= 10)
		putnbr(n / 10, cnt);
	c = (n % 10) + '0';
	putchar(c);
	(*cnt)++;
}

static void	puthex(unsigned int n, char *base, int *cnt)
{
	if (n >= 16)
		puthex(n / 16, base, cnt);
	*cnt += putchar(base[n % 16]);
}

int	ft_printf(const char *format, ...)
{
	int		cnt;
	int		i;
	va_list	args;

	i = 0;
	cnt = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
				cnt += putstr(va_arg(args, char *));
			else if (format[i] == 'd')
				putnbr(va_arg(args, int), &cnt);
			else if (format[i] == 'x')
				puthex(va_arg(args, unsigned int), "0123456789abcdef", &cnt);
		}
		else
			cnt += putchar(format[i]);
		i++;
	}
	va_end(args);
	return (cnt);
}

int	main(void)
{
	int	n;

	n = ft_printf("Numero: %x\n", 10);
	ft_printf("Retorno: %d\n", n);
}
