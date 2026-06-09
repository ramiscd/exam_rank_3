#include <unistd.h>

void sort_str(char *str, int len)
{
	int i = 0;
	int j;
	char tmp;

	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if(str[i] > str[j])
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

void solve(char *str, char *res, int *used, int pos, int len)
{
	int i = 0;

	if(pos == len)
	{
		write(1, res, len);
		write(1, "\n", 1);
		return;
	}

	while (i < len)
	{
		if (used[i] == 0)
		{
			used[i] = 1;
			res[pos] = str[i];

			solve(str, res, used, pos + 1, len);
			used[i] = 0;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	char res[255]; // buffer para montar a palavra final
	int used[255]; // array para macarcar se a letra [i] já foi usada (0 ou 1);
	int len = 0;
	int i = 0;

	if (ac != 2)
		return 1;

	while (av[1][len])
		len++;

	sort_str(av[1], len);

	while (i < len)
	{
		used[i] = 0;
		i++;
	}

	solve(av[1], res, used, 0, len);
	return 0;
}