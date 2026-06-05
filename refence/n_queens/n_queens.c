// Para praticar
#include <unistd.h>
#include <stdlib.h>

int is_safe(int pos[], int row, int col)
{
	int i = 0;
	while (i < row)
	{
		if(pos[i] == col)
			return 0;
		if(abs(row - i) == abs(col - pos[i]))
			return 0;
		i++;
	}
	return 1;
}
void print_solution(int pos[], int n)
{
	int i = 0;

	while (i < n)
	{
		char c = pos[i] + '0';
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
}

void solve(int pos[], int row, int n)
{
	if (row == n)
	{
		print_solution(pos, n);
		return ;
	}

	int col = 0;

	while (col < n)
	{
		if(is_safe(pos, row, col))
		{
			pos[row] = col;
			solve(pos, row + 1, n);
		}
		col++;
	}
}

int main()
{
	int pos[10];
	solve(pos, 0, 4);
}