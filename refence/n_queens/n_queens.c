#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

/*
	Verifica se posso colocar
	uma rainha em:
	linha = row
	coluna = col
*/
int is_safe(int pos[],int row, int col)
{
	int i = 0;

	/*
		Verifica todas as rainhas
		das linhas anteriores
	*/
	while (i < row)
	{
		/*
			Conflito vertical

			Se a coluna da rainha antiga
			for igual à nova coluna
		*/

		if (pos[i] == col)
			return 0;
		
		/*
			Conflito diagonal

			Se a distância das linhas
			for igual à distância das colunas
		*/
		if (abs(row - i) == abs(col - pos[i]))
			return 0;
		
		i++;
	}
	
	/*
		Nenhum conflito
	*/
	return 1;
}

/*
	Imprime uma solução

	Ex:
	1302
*/
void print_solution(int pos[], int n)
{
	int i = 0;

	while (i < n)
	{
		ft_putchar(pos[i] + '0');
		i++;
	}
	ft_putchar('\n');
}
/*
	Tenta resolver o tabuleiro
	uma linha por vez
	row = linha atual que preciso resolver
*/
void solve(int pos[], int row, int n)
{

	/*
		Se row == n
		significa que colocamos todas as rainhas
	*/
	if (row == n)
	{
		print_solution(pos, n);
		return ;
	}

	int col = 0;

	/* Tenta todas as colunas da linha atual */
	while (col < n)
	{

		/* Se posição válida */
		if (is_safe(pos, row, col))
		{
			/* Coloca rainha */
			pos[row] = col;

			/* Tenta próxima linha */
			solve(pos, row + 1, n);
		}
		/* Tenta próxima coluna */
		col++;
	}
}

int main(void)
{
	int pos[10];

	/*
		Começa da linha 0
		em um tabuleiro 4x4
	*/
	solve(pos, 0, 4);
}
