// Ler todo o buffer size e salvar em uma variavel.
// echo "test abc test abc" | ./filter abc > out1.txt
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	char buffer[1024];
	char *fileName = "test.txt";
	int file = open(fileName, O_RDONLY); // Retorna o fd.
	read(file, buffer ,sizeof(buffer));
	printf("\n%s\n", buffer);


	// verificar "abc" em "abcdef" -> ***def
	char *alvo = "abc";
	memmem()

	return(0);
}
