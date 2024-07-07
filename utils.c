#include "philo.h"
#include <stdio.h>

void 	print_eror(char *str)
{
	printf("%s", str);
	exit(1);
}

long  long int    ft_atoi(const char *str)
{
        int                                             i;
        int                                             s;
        unsigned long long int  r;

        i = 0;
        s = 1;
        r = 0;
        while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
                i++;
        if (str[i] == '-' || str[i] == '+')
        {
                if (str[i] == '-')
                        s = s * (-1);
                i++;
        }
        while (str[i] >= 48 && str[i] <= 57)
        {
                r = (r * 10) + (str[i] - 48);
                if (s == 1 && r > 9223372036854775807)
                        return (-1);
                if (s == (-1) && r > 9223372036854775807)
                        return (0);
                i++;
        }
        return (r * s);
}
