#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void	put_string(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		*len += write(1, str, 1);
		str++;
	}
}

void	put_digit(long long int nbr, int base, int * len)
{
	char *hexdigit = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		put_digit(nbr / base, base, len);
	*len += write(1, &hexdigit[nbr % base], 1);
}


int ft_printf(const char *format, ... )
{
	int	len = 0;
	va_list ptr;
	va_start(ptr, format);
	while (*format)
	{
		if (*format == '%' && (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x'))
		{
			format++;
			if (*format == 's')
				put_string(va_arg(ptr, char *), &len);
			else if (*format == 'd')
				put_digit((long long int)va_arg(ptr, int), 10, &len);
			else if (*format == 'x')
				put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);
		}
		else
		{
			len += write(1, format, 1);
		}
		format++;
	}
	return (va_end(ptr),len);
}

/*int main()
{
	//ft_printf("%s", "hello");
	//ft_printf("%d", -2147483648);
	ft_printf("%x", -2147483648);
	//ft_printf("hex of 42 if %x", 42);
}*/
