#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
int printnum(va_list num);
int printstr(va_list pr);
int comp(const char b, va_list p);
/**
 * _printf - main intrance for print
 * @format: the arguments
 * @...: the variadic argument
 * Return: 0 always success
 */
int _printf(const char *format, ...)
{
	va_list print;

	int counter = 0;

	int i;

	if (format == NULL)
		return (-1);

	va_start(print, format);
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
			{
				_putchar('%');
				counter++;
				i++;
			}
			else if (format[i + 1] == '\0')
			{
				return (-1);
			}
			else
			{
				counter = counter + comp(format[i + 1], print);
				i++;
			}
		}
		else
		{
			_putchar(format[i]);
			counter++;
		}
	}
	va_end(print);
	return (counter);
}
/**
 * comp - compare the format
 * @b: the format argument
 * @p: th argument to be printed
 * Return: the number of printed char after calling a func.
 */
int comp(const char b, va_list p)
{
	if (b == 's')
	{
		return (printstr(p));
	}
	if (b == 'd' || b == 'i')
	{
		return (printnum(p));
	}
	_putchar('%');
	_putchar(b);
	return (2);
}
/**
 * printstr - prints a string
 * @pr: the argument
 * Return: the number of printed char
 */
int printstr(va_list pr)
{
	char *str;

	int i;

	str = va_arg(pr, char*);

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else
	{
		for (i = 0; str[i] != '\0'; i++)
		{
			_putchar(str[i]);
		}
		return (i);
	}
}
/**
 * _putchar - putchar function
 * @c: the char to be printed
 * Return: char to stdout
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * printnum - prints num
 * @num: the input
 * Return: the number
 */
int printnum(va_list num)
{
	long int n;
	int i, temp, base;

	i = 0;
	n = va_arg(num, int);

	if (n < 0)
	{
		_putchar('-');
		i++;
		n = -n;
	}
	if (n >= 0 && n <= 9)
	{
		_putchar(n + 48);
		i++;
	}
	if (n > 9)
	{
		base = 10;

		while (n / base > 9)
		{
			base = base * 10;
		}
		while (base > 0)
		{
			temp = n / base;
			n = n % base;
			_putchar(temp + 48);
			base = base / 10;
			i++;
		}
	}
	return (i);
}
