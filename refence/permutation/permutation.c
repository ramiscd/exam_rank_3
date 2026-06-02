#include <unistd.h>

void	sort(char *str, int len);
void	rotate(char *str, int start, int end, int reverse);
void	solve(char *str, int start, int end);

int	main(int argc, char **argv)
{
	char	*arg;
	int		len;

	if (argc != 2)
		return (1);
	arg = argv[1];
	len = 0;
	while (arg[len])
		len++;
	sort(arg, len);
	solve(arg, 0, len -1);
	return (0);
}

void	solve(char *str, int start, int end)
{
	int	i;

	if (start == end)
	{
		i = 0;
		while (str[i])
			write(1, &str[i++], 1);
		write(1, "\n", 1);
		return ;
	}
	i = start;
	while (i <= end)
	{
		rotate(str, start, i, 0);
		solve(str, start +1, end);
		rotate(str, start, i, 1);
		i++;
	}
}

void	rotate(char *str, int start, int end, int reverse)
{
	char	tmp;
	int		i;

	if (!reverse)
	{
		tmp = str[end];
		i = end;
		while (i > start)
		{
			str[i] = str[i -1];
			i--;
		}
		str[start] = tmp;
	}
	else
	{
		tmp = str[start];
		i = start;
		while (i < end)
		{
			str[i] = str[i +1];
			i++;
		}
		str[end] = tmp;
	}
}

void	sort(char *str, int len)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < len -1)
	{
		j = i +1;
		while (j < len)
		{
			if (str[i] > str[j])
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
