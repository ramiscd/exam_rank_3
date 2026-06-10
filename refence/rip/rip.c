#include <unistd.h>

// Função auxiliar para o tamanho da string
int str_len(char *s) {
	int i = 0;
	while (s[i])
		i++;
	return i;
}

// Verifica se a string está balanceada (ignora os espaços ' ')
int esta_valido(char *s) {
	int balanco = 0;
	for (int i = 0; s[i]; i++) {
		if (s[i] == '(') balanco++;
		if (s[i] == ')') balanco--;
		if (balanco < 0) return 0; // Fechou sem abrir
	}
	return (balanco == 0);
}

// O Backtracking ÚNICO
void resolver(char *s, int indice, int removidos, int alvo_remocoes) {
	// Poda: se passou do limite de remoções, para.
	if (removidos > alvo_remocoes) return;

	// Se chegou ao fim da string
	if (s[indice] == '\0') {
		if (removidos == alvo_remocoes && esta_valido(s)) {
			write(1, s, str_len(s));
			write(1, "\n", 1);
		}
		return;
	}

	// Se for um parêntese, temos duas escolhas: remover ou manter
	if (s[indice] == '(' || s[indice] == ')') {
		char original = s[indice];
		
		// Opção 1: REMOVER (transforma em espaço)
		s[indice] = ' ';
		resolver(s, indice + 1, removidos + 1, alvo_remocoes);
		
		// Restaura para a Opção 2: MANTER
		s[indice] = original;
	}

	// Avança mantendo o caractere atual
	resolver(s, indice + 1, removidos, alvo_remocoes);
}

int main(int ac, char **av) {
	if (ac != 2 || av[1][0] == '\0') return 1;

	char *str = av[1];
	int abre = 0, fecha = 0;

	// MATEMÁTICA DO MÍNIMO: Descobre exatamente quantos precisamos remover
	for (int i = 0; str[i]; i++) {
		if (str[i] == '(') abre++;
		else if (str[i] == ')') {
			if (abre > 0) abre--;
			else fecha++; // Sobrou um ')' sem par
		}
	}
	int total_remover = abre + fecha; // Esse é o nosso "alvo"

	// Dispara o backtracking
	resolver(str, 0, 0, total_remover);
	return 0;
}