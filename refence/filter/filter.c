#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

int validate_args(int ac, char **av)
{
	if(ac != 2)
		return 1;
	if (!av[1] || av[1][0] == '\0')
		return 1;
	return 0;
}

char *read_all_stdin(void)
{
	char tmp[BUF_SIZE]; // buffer temporário: recebe cada bloco lido pelo read()
	char *buffer = NULL; // buffer final: acumula todo o conteúdo do stdin
	int bytes; // quantidade de bytes retornados pelo read() em cada iteração
	int len = 0; // tamanho atual do buffer acumulado (controle de crescimento)

	while ((bytes = read(0, tmp, BUF_SIZE)) > 0)
	{
		char *new_buf = realloc(buffer, len + bytes + 1);
		if (!new_buf)
			return NULL;

		buffer = new_buf;

		memmove(buffer + len, tmp, bytes);

		len += bytes;
		buffer[len] = '\0';
	}
	return buffer;
}

void write_stars(int len)
{
	while (len--)
		write(1, "*", 1);
}

void replace_pattern(char *buffer, char *pattern)
{
	char *cur; // cursor de leitura: posição atual dentro do buffer
	char *match; // ponteiro para a posição onde o pattern foi encontrado
	int len; // tamanho do pattern (usado para comparar e avançar o cursor)

	cur = buffer;
	len = strlen(pattern);

	while((match = memmem(cur, strlen(cur), pattern, len)))
	{
		write(1, cur, match - cur);
		write_stars(len);
		cur = match + len;
	}

	write(1, cur, strlen(cur));
}

int main(int ac, char **av)
{
	if (validate_args(ac, av))
		return 1;
	char *s = read_all_stdin();
	if (!s)
	{
		perror("Error");
		return 1;
	}
	replace_pattern(s, av[1]);
	free(s);
	return 0;
}