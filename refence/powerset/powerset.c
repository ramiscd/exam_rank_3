#include <stdio.h>
#include <stdlib.h>

void	solve(int *set, int *sub, int size, int target, int idx, int s_idx, int sum);

int	main(int argc, char **argv)
{
	int	*set, *sub;
	int	i;

	if (argc < 2)
		return (1);
	set = malloc(sizeof(int) * (argc -2));
	sub = malloc(sizeof(int) * (argc -2));
	if (!set || !sub)
		return (1);
	i = -1;
	while (++i < argc -2)
		set[i] = atoi(argv[i +2]);
	solve(set, sub, argc -2, atoi(argv[1]), 0, 0, 0);
	free(set);
	free(sub);
	return (0);
}

void	solve(int *set, int *sub, int size, int target, int idx, int s_idx, int sum)
{
	int	i;

	if (idx == size)
	{
		if (target == sum)
		{
			i = -1;
			while (++i < s_idx)
				printf("%d%s", sub[i], (i < s_idx -1) ? " " : "");
			printf("\n");
		}
		return ;
	}
	sub[s_idx] = set[idx];
	solve(set, sub, size, target, idx +1, s_idx +1, sum + set[idx]);
	solve(set, sub, size, target, idx +1, s_idx, sum);
}