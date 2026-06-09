#include <unistd.h>

// 1. Ordenação normal (Selection Sort)
void	sort_str(char *str, int len)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
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

// 2. A recursão simples e sem matemática de rotação
void	solve(char *str, char *res, int *used, int pos, int len)
{
	int	i = 0;

	// Se a posição atual chegou no tamanho da string, a palavra tá pronta
	if (pos == len)
	{
		write(1, res, len);
		write(1, "\n", 1);
		return ;
	}

	while (i < len)
	{
		// Se a letra ainda NÃO foi usada na palavra atual
		if (used[i] == 0)
		{
			used[i] = 1;           // MARCA: "estou usando esta letra"
			res[pos] = str[i];     // Coloca a letra na posição atual do resultado
			
			// Chama a função para preencher a PRÓXIMA posição (pos + 1)
			solve(str, res, used, pos + 1, len);
			
			used[i] = 0;           // DESMARCA (Backtrack): "libera a letra para a próxima tentativa"
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	char	res[255];   // Buffer para montar a palavra final
	int		used[255];  // Array para marcar se a letra [i] já foi usada (0 ou 1)
	int		len = 0;
	int		i = 0;

	if (ac != 2)
		return (1);

	while (av[1][len])
		len++;
		
	sort_str(av[1], len);
	
	// Zera o array de "usados"
	while (i < len)
	{
		used[i] = 0;
		i++;
	}

	// Chama a função começando na posição 0
	solve(av[1], res, used, 0, len);
	return (0);
}