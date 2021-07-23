#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int		round_ceil(float n)
{
	int		sign;
	int		i;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		n *= -1;
		n--;
	}
	i = 0;
	while (i < n)
		i++;
	return (sign * i);
}

int		round_floor(float n)
{
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	if (n < 0)
	{
		sign = -1;
		n *= -1;
		while (i <= n)
			i++;
	}
	else
	{
		while ((n - i) > 1)
			i++;
	}
	return (sign * i);
}

int		 main()
{
	float f = 0.500;

	printf("my_ceil_f: %d\n", round_ceil(f));
	printf("real_ceil_f: %d\n", (int)ceilf(f));
	printf("my_floor_f: %d\n", round_floor(f));
	printf("real_floor_f: %d\n", (int)floorf(f));
}