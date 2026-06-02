# N Queens - Guia de Estudo para a Prova da 42

## Objetivo do exercício

Colocar N rainhas em um tabuleiro NxN de forma que nenhuma rainha ataque outra.

Uma rainha ataca:

* Na horizontal
* Na vertical
* Na diagonal

Como colocamos exatamente uma rainha por linha, não precisamos verificar conflito horizontal.

Precisamos verificar apenas:

* Coluna
* Diagonal

---

# O segredo do exercício

O exercício NÃO é sobre xadrez.

O exercício é sobre:

* Recursão
* Backtracking
* Explorar possibilidades
* Voltar quando uma escolha não funciona

---

# Representação do tabuleiro

Não precisamos guardar o tabuleiro inteiro.

Em vez disso usamos:

```c
int pos[10];
```

Onde:

* Índice = linha
* Valor = coluna

Exemplo:

```c
pos[0] = 1;
pos[1] = 3;
pos[2] = 0;
pos[3] = 2;
```

Significa:

```txt
linha 0 -> coluna 1
linha 1 -> coluna 3
linha 2 -> coluna 0
linha 3 -> coluna 2
```

Visualmente:

```txt
.Q..
...Q
Q...
..Q.
```

---

# Como pensar no array

Sempre lembrar:

```txt
pos[i]
```

Significa:

```txt
coluna da rainha da linha i
```

Exemplo:

```c
pos[2] = 3;
```

Significa:

```txt
linha 2
coluna 3
```

---

# Função is_safe

Objetivo:

```c
int is_safe(int pos[], int row, int col);
```

Pergunta:

```txt
Posso colocar uma rainha
na linha row
e coluna col?
```

---

# O que comparar

Não precisamos verificar todas as rainhas.

Só verificamos:

```txt
linhas anteriores
```

Porque as próximas ainda não existem.

Por isso:

```c
while (i < row)
```

---

# Conflito vertical

Duas rainhas estão em conflito se estiverem na mesma coluna.

```c
if (pos[i] == col)
	return (0);
```

Explicação:

```txt
pos[i]
=
coluna da rainha antiga

col
=
coluna da nova rainha
```

Se forem iguais:

```txt
mesma coluna
```

---

# Conflito diagonal

Duas rainhas estão em diagonal quando:

| diferença das linhas | = | diferença das colunas |

Em código:

```c
abs(row - i) == abs(col - pos[i])
```

Exemplo:

```txt
linha 0 coluna 1
linha 2 coluna 3
```

Diferença linhas:

2

Diferença colunas:

2

Logo:

```txt
conflito diagonal
```

---

# Estrutura mental do is_safe

```txt
para cada rainha antiga

	se mesma coluna
		return falso

	se diagonal
		return falso

retorna verdadeiro
```

---

# Print da solução

Exemplo:

```c
1302
```

Não é um número.

Significa:

```txt
linha 0 -> coluna 1
linha 1 -> coluna 3
linha 2 -> coluna 0
linha 3 -> coluna 2
```

Código:

```c
ft_putchar(pos[i] + '0');
```

Importante:

```c
'0'
```

e não:

```c
'\0'
```

---

# O que é Backtracking

Backtracking significa:

```txt
tenta
falhou
volta
tenta outra opção
```

Exatamente como explorar um labirinto.

---

# O papel da recursão

A função solve NÃO resolve o tabuleiro inteiro.

Ela resolve apenas:

```txt
uma linha
```

E delega o restante para a próxima chamada recursiva.

---

# Estrutura da função solve

```c
solve(pos, row, n);
```

Onde:

```txt
pos = estado atual do tabuleiro

row = linha que estou resolvendo

n = tamanho do tabuleiro
```

---

# Caso base

Quando:

```c
row == n
```

Significa:

```txt
todas as rainhas foram colocadas
```

Então:

```c
print_solution(pos, n);
return ;
```

---

# Caso recursivo

Para a linha atual:

```txt
tentar todas as colunas
```

```c
col = 0;

while (col < n)
```

---

# Se a posição for válida

```c
if (is_safe(pos, row, col))
```

Coloca a rainha:

```c
pos[row] = col;
```

Depois tenta resolver a próxima linha:

```c
solve(pos, row + 1, n);
```

---

# Onde acontece o backtracking?

Muita gente procura algo como:

```txt
desfazer jogada
```

Mas não existe.

Quando a recursão retorna:

```c
solve(...)
```

o programa volta automaticamente para o while anterior.

Então ele tenta a próxima coluna.

Além disso:

```c
pos[row] = col;
```

sobrescreve automaticamente o valor antigo.

Não precisamos limpar nada.

---

# Fluxo mental do algoritmo

```txt
resolver linha atual

para cada coluna

	se posição segura

		coloca rainha

		resolve próxima linha

quando voltar

	tenta próxima coluna
```

---

# Como pensar durante a prova

NÃO pense:

"preciso resolver o tabuleiro inteiro"

Pense:

"preciso resolver apenas esta linha"

A recursão resolverá o resto.

---

# Erros comuns

## Erro 1

Trocar row por col

Errado:

```c
if (pos[i] == row)
```

Correto:

```c
if (pos[i] == col)
```

---

## Erro 2

Trocar argumentos

Errado:

```c
is_safe(pos, col, row);
```

Correto:

```c
is_safe(pos, row, col);
```

---

## Erro 3

Esquecer incrementar col

Errado:

```c
while (col < n)
{
	...
}
```

Sem:

```c
col++;
```

Resultado:

```txt
loop infinito
```

---

# Frase para decorar

Se eu travar na prova:

```txt
resolver linha atual

tentar todas as colunas

se for seguro
	colocar rainha
	resolver próxima linha

quando voltar
	tentar próxima coluna
```

Essa frase é o algoritmo inteiro.
