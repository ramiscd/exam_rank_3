#include <stdio.h>
#include <stdlib.h>

void print_subset(int *subset, int size) {
	if (size == 0) {
		printf("\n");
		return;
	}
	for (int i = 0; i < size; i++) {
		printf("%d%s", subset[i], (i == size - 1) ? "" : " ");
	}
	printf("\n");
}

void backtrack(int *set, int set_size, int index, int *subset, int subset_size, int current_sum, int target) {
	if (index == set_size) {
		if (current_sum == target) {
			print_subset(subset, subset_size);
		}
		return;
	}

	backtrack(set, set_size, index + 1, subset, subset_size, current_sum, target);

	subset[subset_size] = set[index];
	backtrack(set, set_size, index + 1, subset, subset_size + 1, current_sum + set[index], target);
}

int main(int ac, char **av)
{
	if (ac < 2)
		return 1;

	if(av[1][0] == '0' && av[1][1] == '\0')
	{
		printf("\n");
		return 0;
	}

	int target = atoi(av[1]);
	int set_size = ac - 2;

	if (set_size <= 0)
		return 1;

	int *set = malloc(sizeof(int) * set_size);
	int *subset = malloc(sizeof(int) * set_size);

	if(!set || !subset)
	{
		free(set);
		free(subset);
		return 1;
	}

	for (int i = 0; i < set_size; i++)
	{
		set[i] = atoi(av[i + 2]);
	}

	backtrack(set, set_size, 0, subset, 0, 0, target);

	free(set);
	free(subset);
	return 0;
}